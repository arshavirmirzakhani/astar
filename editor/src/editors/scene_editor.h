#pragma once
#include "engine/game.h"
#include "imgui/imgui.h"
#include <SDL3/SDL.h>

std::string selected_scene;
unsigned int selected_scene_index;

void show_scene_editor(Game& game, SDL_Renderer* renderer) {
	ImGui::Begin("Scene editor");

	ImGui::BeginGroup();

	if (ImGui::BeginChild("Scenelist", ImVec2(200, 500), true)) {
		int index = 0;
		for (const auto& [name, scene] : game.scenes) {
			bool selected = (selected_scene_index == index);
			if (ImGui::Selectable(name.c_str(), selected)) {
				selected_scene_index = index;
				selected_scene	     = name;
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