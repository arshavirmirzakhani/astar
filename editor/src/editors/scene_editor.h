#pragma once
#include "engine/game.h"
#include "imgui/imgui.h"
#include <SDL.h>

static std::string selected_scene;
static unsigned int selected_scene_index;
static char new_scene_name[255];

static ImVec2 scene_pan_offset = ImVec2(0, 0);
static float scene_view_zoom   = 1.0f;
static float scene_prev_zoom   = scene_view_zoom;

SDL_Texture* scene_editor_preview_texture = nullptr;
SDL_Texture* scene_editor_bg_texture	  = nullptr;
SDL_Texture* scene_editor_tilemap_texture = nullptr;
SDL_Texture* scene_editor_objects_texture = nullptr;
SDL_Rect scene_editor_preview_rect;

static bool is_scene_changed	     = true;
static bool is_scene_changed_bg	     = true;
static bool is_scene_changed_tilemap = true;
static bool is_scene_changed_objects = true;

static std::string selected_object_in_scene = "";
static char new_object_name[255];
static std::string selected_type = "";

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
				game.scenes[name]	 = Scene();
				selected_scene		 = name;
				is_scene_changed	 = true;
				is_scene_changed_objects = true;
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

		if (ImGui::Button("New Object ")) {
			ImGui::OpenPopup("new_object_popup");
		}

		if (ImGui::BeginPopup("new_object_popup")) {
			ImGui::InputText("Name", new_object_name, 255);

			if (ImGui::BeginCombo("Select Object Type", selected_type.empty() ? "None" : selected_type.c_str())) {
				for (auto& [name, _] : game.object_types) {
					bool is_selected = (selected_type == name);
					if (ImGui::Selectable(name.c_str(), is_selected)) {
						selected_type = name;
					}
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			if (ImGui::Button("Create")) {
				std::string name = new_object_name;
				if (!name.empty() && !selected_type.empty() && game.object_types.find(name) == game.object_types.end()) {
					game.scenes[selected_scene].add_object(new_object_name, Object(selected_type));
					selected_object_in_scene = name;
				}
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}

		for (auto& [name, object] : game.scenes[selected_scene].objects) {
			bool is_selected = (selected_object_in_scene == name);
			if (ImGui::Selectable(name.c_str(), is_selected, 0, ImVec2(200, 0))) {
				selected_object_in_scene = name;
			}
		}

		if (selected_object_in_scene != "") {
			Object& object = game.scenes[selected_scene].objects[selected_object_in_scene];

			float position[2] = {object.position_x, object.position_y};

			ImGui::SetNextItemWidth(350);

			ImGui::InputFloat2("Position", position);

			object.position_x = position[0];
			object.position_y = position[1];

			is_scene_changed = true;
		}

		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();

		ImVec2 canvas_size = ImGui::GetContentRegionAvail();
		ImGui::BeginChild("SceneCanvas", canvas_size, true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		auto scene_buffer = std::vector<unsigned char>(game.scenes[selected_scene].width * 8 * game.scenes[selected_scene].height * 8, 0);

		ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
		if (canvas_size.x <= 0 || canvas_size.y <= 0) {
			ImGui::EndChild();
			ImGui::EndGroup();
			ImGui::EndGroup();
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

			// Render to scene texture
			if (scene_editor_bg_texture)
				SDL_DestroyTexture(scene_editor_bg_texture);
			scene_editor_bg_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
								    game.scenes[selected_scene].width * 8, game.scenes[selected_scene].height * 8);
			SDL_SetTextureScaleMode(scene_editor_bg_texture, SDL_ScaleModeNearest);
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
					scene_editor_preview_rect = {(int)x, (int)y, 1, 1};
					SDL_RenderFillRect(renderer, &scene_editor_preview_rect);
				}
			}

			SDL_SetRenderTarget(renderer, oldTarget);
			is_scene_changed_bg = false;

			if (scene_editor_objects_texture)
				SDL_DestroyTexture(scene_editor_objects_texture);
			scene_editor_objects_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
									 game.scenes[selected_scene].width * 8, game.scenes[selected_scene].height * 8);

			SDL_SetRenderTarget(renderer, scene_editor_objects_texture);
			for (const auto& [name, object] : game.scenes[selected_scene].objects) {
				SDL_Rect selection_rect = {(int)object.position_x - 1, (int)object.position_y - 1, 10, 10};

				// Rendering

				// Draw selected object with highlight
				if (name == selected_object_in_scene) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow border
					SDL_RenderDrawRect(renderer, &selection_rect);
				}
			}

			SDL_SetRenderTarget(renderer, oldTarget);
		}

		scene_editor_preview_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
								 game.scenes[selected_scene].width * 8, game.scenes[selected_scene].height * 8);

		SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);
		SDL_SetRenderTarget(renderer, scene_editor_preview_texture);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, scene_editor_bg_texture, nullptr, nullptr);
		SDL_RenderCopy(renderer, scene_editor_objects_texture, nullptr, nullptr);

		SDL_SetRenderTarget(renderer, oldTarget);
		is_scene_changed = false;

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