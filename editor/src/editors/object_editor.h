#pragma once
#include "engine/game.h"
#include "imgui/imgui.h"

static char new_object_type_name[255] = "";
static char new_animation_name[255]   = "";

static std::string selected_object_type = "";
static std::string selected_animation	= "";

void show_object_editor(Game& game) {
	ImGui::Begin("Object Editor");

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
	for (auto& [name, type] : game.object_types) {
		bool is_selected = (selected_object_type == name);
		if (ImGui::Selectable(name.c_str(), is_selected)) {
			selected_object_type = name;
			selected_animation   = "";
		}
	}

	ImGui::Separator();

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
				if (!anim_name.empty() && obj_type.all_animation_states.find(anim_name) ==
							      obj_type.all_animation_states.end()) {
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
		if (ImGui::BeginCombo("Select Animation",
				      selected_animation.empty() ? "None" : selected_animation.c_str())) {
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

		// === Show sprite names in selected animation ===
		if (!selected_animation.empty()) {
			auto& sprites = obj_type.all_animation_states[selected_animation];

			ImGui::Separator();
			ImGui::Text("Sprites in Animation '%s':", selected_animation.c_str());
			if (sprites.empty()) {
				ImGui::TextDisabled("(No sprites)");
			} else {
				for (size_t i = 0; i < sprites.size(); ++i) {
					ImGui::BulletText("[%zu] %s", i, sprites[i].c_str());
				}
			}
		}
	}

	ImGui::End();
}
