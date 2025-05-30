#pragma once
#include "engine/game.h"
#include "imgui/imgui.h"
#include "imgui/imgui_stdlib.h"

static std::string selected_init_scene;

void show_settings_editor(Game& game) {
	ImGui::Begin("Game settings");

	ImGui::BeginGroup();

	ImGui::InputText("Game name", &game.name);

	if (ImGui::BeginCombo("Init Scene", game.init_scene.empty() ? "None" : game.init_scene.c_str())) {
		for (auto& [name, _] : game.scenes) {
			bool is_selected = (game.init_scene == name);
			if (ImGui::Selectable(name.c_str(), is_selected)) {
				game.init_scene = name;
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::EndGroup();

	ImGui::End();
}