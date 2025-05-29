#pragma once
#include "engine/game.h"
#include "imgui/imgui.h"
#include <SDL3/SDL.h>

static std::string selected_scene;
static unsigned int selected_scene_index;
static char new_scene_name[255];

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

	ImGui::End();
}