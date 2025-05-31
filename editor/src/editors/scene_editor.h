#pragma once
#include "engine/game.h"
#include "imgui/imgui.h"
#include <SDL3/SDL.h>

static std::string selected_scene;
static unsigned int selected_scene_index;
static char new_scene_name[255];

static ImVec2 scene_pan_offset = ImVec2(0, 0);
static float scene_view_zoom   = 1.0f;
static float scene_prev_zoom   = scene_view_zoom;

SDL_Texture* scene_editor_preview_texture = nullptr;
SDL_Texture* scene_editor_bg_texture	  = nullptr;
SDL_Texture* scene_editor_tilemap	  = nullptr;
SDL_Texture* scene_editor_objects	  = nullptr;
SDL_FRect scene_editor_preview_rect;

static bool is_scene_changed	     = true;
static bool is_scene_changed_bg	     = true;
static bool is_scene_changed_tilemap = true;
static bool is_scene_changed_objects = true;

void show_scene_editor(Game& game, SDL_Renderer* renderer) {
	ImGui::Begin("Scene editor");

	ImGui::BeginGroup();

	if (ImGui::Button("New Scene")) {
		ImGui::OpenPopup("new_scene_popup");
	}

	if (ImGui::BeginPopup("new_scene_popup")) {
		ImGui::InputText("Name", new_scene_name, 255);
		if (ImGui::Button("Create")) {
			std::string name = new_scene_name;
			if (!name.empty() && game.scenes.find(name) == game.scenes.end()) {
				game.scenes[name] = Scene();
				selected_scene	  = name;
			}
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}

	if (ImGui::BeginChild("Scenelist", ImVec2(200, 500), true)) {
		int index = 0;
		for (const auto& [name, scene] : game.scenes) {
			bool selected = (selected_scene == name);
			if (ImGui::Selectable(name.c_str(), selected)) {
				selected_scene = name;
			}
			if (selected)
				ImGui::SetItemDefaultFocus();
			++index;
		}
	}
	ImGui::EndChild();
	ImGui::EndGroup();

	ImGui::SameLine();

	ImGui::BeginGroup();

	if (selected_scene != "") {

		ImGui::BeginGroup();

		ImGui::SetNextItemWidth(300);
		if (ImGui::InputInt("Scene Width", &game.scenes[selected_scene].width)) {
			SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "scene changed width");
			is_scene_changed    = true;
			is_scene_changed_bg = true;
		}

		ImGui::SetNextItemWidth(300);
		if (ImGui::InputInt("Scene Height", &game.scenes[selected_scene].height)) {
			SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "scene changed height");
			is_scene_changed    = true;
			is_scene_changed_bg = true;
		}

		if (game.scenes[selected_scene].width < 1) {
			game.scenes[selected_scene].width = 1;
		}

		if (game.scenes[selected_scene].height < 1) {
			game.scenes[selected_scene].height = 1;
		}

		ImGui::EndGroup();

		ImGui::NewLine();

		ImGui::BeginGroup();

		ImVec2 canvas_size = ImGui::GetContentRegionAvail();
		ImGui::BeginChild("SceneCanvas", canvas_size, true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		auto scene_buffer = std::vector<unsigned char>(game.scenes[selected_scene].width * 8 * game.scenes[selected_scene].height * 8, 0);

		ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
		if (canvas_size.x <= 0 || canvas_size.y <= 0) {
			ImGui::EndChild();
			ImGui::End();
			return;
		}

		// Zoom center
		float wheel = ImGui::GetIO().MouseWheel;
		if (wheel != 0.0f && ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows)) {
			scene_prev_zoom = scene_view_zoom;
			scene_view_zoom *= (wheel > 0) ? 1.1f : 0.9f;
			scene_view_zoom	   = std::clamp(scene_view_zoom, 0.1f, 100.0f);
			ImVec2 center	   = ImVec2(canvas_size.x * 0.5f, canvas_size.y * 0.5f);
			float factor	   = scene_view_zoom / scene_prev_zoom;
			scene_pan_offset.x = center.x + (scene_pan_offset.x - center.x) * factor;
			scene_pan_offset.y = center.y + (scene_pan_offset.y - center.y) * factor;
		}

		// Drag/Pan
		ImGui::InvisibleButton("canvas", canvas_size, ImGuiButtonFlags_MouseButtonLeft);
		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			ImVec2 delta = ImGui::GetIO().MouseDelta;
			scene_pan_offset.x += delta.x;
			scene_pan_offset.y += delta.y;
		}

		if (is_scene_changed) {

			if (is_scene_changed_bg) {
				// Render to scene texture
				if (scene_editor_bg_texture)
					SDL_DestroyTexture(scene_editor_bg_texture);
				scene_editor_bg_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
									    game.scenes[selected_scene].width * 8, game.scenes[selected_scene].height * 8);
				SDL_SetTextureScaleMode(scene_editor_bg_texture, SDL_SCALEMODE_NEAREST);
				SDL_SetTextureBlendMode(scene_editor_bg_texture, SDL_BLENDMODE_BLEND);

				SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);
				SDL_SetRenderTarget(renderer, scene_editor_bg_texture);

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);

				for (unsigned int y = 0; y < (unsigned int)game.scenes[selected_scene].height * 8; y++) {
					for (unsigned int x = 0; x < (unsigned int)game.scenes[selected_scene].width * 8; x++) {

						unsigned char pixel = scene_buffer[y * game.scenes[selected_scene].width * 8 + x];
						Color color	    = game.pallete.colors[pixel];

						if (color.a == 0 || pixel == 0) {
							continue;
						}

						SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
						scene_editor_preview_rect = {(float)x, (float)y, 1, 1};
						SDL_RenderFillRect(renderer, &scene_editor_preview_rect);
					}
				}

				SDL_SetRenderTarget(renderer, oldTarget);
				is_scene_changed_bg = false;
			}

			if (scene_editor_preview_texture)
				SDL_DestroyTexture(scene_editor_preview_texture);
			scene_editor_preview_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
									 game.scenes[selected_scene].width * 8, game.scenes[selected_scene].height * 8);

			SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);
			SDL_SetRenderTarget(renderer, scene_editor_preview_texture);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			SDL_RenderTexture(renderer, scene_editor_bg_texture, nullptr, nullptr);

			SDL_SetRenderTarget(renderer, oldTarget);
			is_scene_changed = false;
		}

		// Draw image on canvas
		ImVec2 imageSize = {scene_view_zoom * game.scenes[selected_scene].width * 8, scene_view_zoom * game.scenes[selected_scene].height * 8};
		ImVec2 imagePos	 = ImVec2(canvas_pos.x + scene_pan_offset.x, canvas_pos.y + scene_pan_offset.y);

		ImGui::GetWindowDrawList()->AddImage((ImTextureID)scene_editor_preview_texture, imagePos,
						     ImVec2(imagePos.x + imageSize.x, imagePos.y + imageSize.y));
		ImGui::EndChild();
		ImGui::EndGroup();
	}
	ImGui::EndGroup();

	ImGui::End();
}