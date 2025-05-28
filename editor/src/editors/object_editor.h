#pragma once
#include "engine/game.h"
#include "imgui/imgui.h"
#include <SDL3/SDL.h>

static char new_object_type_name[255] = "";
static char new_animation_name[255]   = "";

static std::string selected_object_type = "";
static std::string selected_animation	= "";

static float object_editor_zoom = 1.0f;

SDL_Texture* object_type_preview_texture = nullptr;
SDL_FRect object_editor_preview_rect;

void show_object_editor(Game& game, SDL_Renderer* renderer) {
	ImGui::Begin("Object Editor");

	ImGui::BeginGroup();
	// === Create new ObjectType ===
	if (ImGui::Button("New Object Type")) {
		ImGui::OpenPopup("new_object_popup");
	}

	if (ImGui::BeginPopup("new_object_popup")) {
		ImGui::InputText("Name", new_object_type_name, 255);
		if (ImGui::Button("Create")) {
			std::string name = new_object_type_name;
			if (!name.empty() && game.object_types.find(name) == game.object_types.end()) {
				game.object_types[name] = ObjectType();
				selected_object_type	= name;
				selected_animation	= "";
			}
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}

	// === ObjectType Selection List ===
	ImGui::Text("Object Types:");
	if (ImGui::BeginChild("SpriteTypeList", ImVec2(200, 500), true)) {
		for (auto& [name, type] : game.object_types) {
			bool is_selected = (selected_object_type == name);
			if (ImGui::Selectable(name.c_str(), is_selected)) {
				selected_object_type = name;
				selected_animation   = "";
			}
		}
	}

	ImGui::EndChild();

	ImGui::EndGroup();

	ImGui::SameLine();

	ImGui::BeginGroup();
	// === Animation State Editor ===
	if (!selected_object_type.empty()) {
		auto& obj_type = game.object_types[selected_object_type];

		ImGui::Text("Selected Object: %s", selected_object_type.c_str());

		// === Add new animation state ===
		if (ImGui::Button("New Animation State")) {
			ImGui::OpenPopup("new_animation_popup");
		}

		if (ImGui::BeginPopup("new_animation_popup")) {
			ImGui::InputText("Animation Name", new_animation_name, 255);
			if (ImGui::Button("Create")) {
				std::string anim_name = new_animation_name;
				if (!anim_name.empty() && obj_type.all_animation_states.find(anim_name) == obj_type.all_animation_states.end()) {
					obj_type.all_animation_states[anim_name] = {};
					selected_animation			 = anim_name;
				}
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}

		// === Animation combo box ===
		if (ImGui::BeginCombo("Select Animation", selected_animation.empty() ? "None" : selected_animation.c_str())) {
			for (auto& [name, _] : obj_type.all_animation_states) {
				bool is_selected = (selected_animation == name);
				if (ImGui::Selectable(name.c_str(), is_selected)) {
					selected_animation = name;
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::SliderFloat("##ZoomSlider", &object_editor_zoom, 0.1f, 100.0f, "%.1fx", ImGuiSliderFlags_Logarithmic);
		// === Show sprite names in selected animation ===
		if (!selected_animation.empty()) {
			auto& sprites = obj_type.all_animation_states[selected_animation];

			ImGui::Separator();
			if (sprites.empty()) {
				ImGui::TextDisabled("(No sprites)");
			} else {
				// === Show sprite names in selected animation ===
				if (!selected_animation.empty()) {
					auto& sprite_datas = obj_type.all_animation_states[selected_animation];

					ImGui::Separator();
					ImGui::Text("Sprites in Animation '%s':", selected_animation.c_str());
					if (sprite_datas.empty()) {
						ImGui::TextDisabled("(No sprites)");
					} else {
						for (const std::pair<std::string, SpriteInfo>& sprite_data : sprite_datas) {
							auto it = game.sprites.find(sprite_data.first);
							if (it == game.sprites.end()) {
								ImGui::TextDisabled("%s (missing sprite)", sprite_data.first.c_str());
								continue;
							}

							auto& sprite = it->second;
							if (sprite.width == 0 || sprite.height == 0 || sprite.sprite_buffer.empty()) {
								ImGui::TextDisabled("%s (empty sprite)", sprite_data.first.c_str());
								continue;
							}

							// Recreate texture only if needed
							static std::string last_previewed_sprite;
							static int last_width  = 0;
							static int last_height = 0;

							bool size_changed   = last_width != sprite.width * 8 || last_height != sprite.height * 8;
							bool sprite_changed = last_previewed_sprite != sprite_data.first;

							if (size_changed || sprite_changed) {
								if (object_type_preview_texture) {
									SDL_DestroyTexture(object_type_preview_texture);
									object_type_preview_texture = nullptr;
								}

								object_type_preview_texture =
								    SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
										      sprite.width * 8, sprite.height * 8);

								SDL_SetTextureBlendMode(object_type_preview_texture, SDL_BLENDMODE_BLEND);
								SDL_SetTextureScaleMode(object_type_preview_texture, SDL_SCALEMODE_NEAREST);

								SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);
								SDL_SetRenderTarget(renderer, object_type_preview_texture);
								SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
								SDL_RenderClear(renderer);

								for (unsigned int y = 0; y < sprite.height * 8; y++) {
									for (unsigned int x = 0; x < sprite.width * 8; x++) {
										uint8_t pixel = sprite.sprite_buffer[y * sprite.width * 8 + x];
										if (pixel == 0)
											continue;

										Color color = game.pallete.colors[pixel];
										if (color.a == 0)
											continue;

										SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
										SDL_FRect rect = {(float)x, (float)y, 1, 1};
										SDL_RenderFillRect(renderer, &rect);
									}
								}

								SDL_SetRenderTarget(renderer, oldTarget);

								last_previewed_sprite = sprite_data.first;
								last_width	      = sprite.width * 8;
								last_height	      = sprite.height * 8;
							}

							ImGui::Text("%s", sprite_data.first.c_str());
							if (object_type_preview_texture) {
								ImGui::Image(
								    (ImTextureID)object_type_preview_texture,
								    ImVec2(sprite.width * 8 * object_editor_zoom, sprite.height * 8 * object_editor_zoom));
							}
						}
					}
				}
			}
		}
	}
	ImGui::EndGroup();
	ImGui::End();
}
