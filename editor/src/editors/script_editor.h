#pragma once
#include "engine/game.h"
#include "imgui/TextEditor.h"
#include "imgui/imgui.h"

static std::string selected_type_name = "";

void show_script_editor(Game& game, TextEditor& editor) {

	ImGui::Begin("Script editor");

	ImGui::BeginGroup();

	// === ObjectType Selection List ===
	ImGui::Text("Object Types:");
	if (ImGui::BeginChild("SpriteTypeList", ImVec2(200, 500), true)) {
		for (auto& [name, type] : game.object_types) {
			bool is_selected = (selected_type_name == name);
			if (ImGui::Selectable(name.c_str(), is_selected)) {
				selected_type_name = name;
			}
		}
	}

	ImGui::EndChild();
	ImGui::EndGroup();

	ImGui::SameLine();

	ImGui::BeginGroup();

	if (selected_type_name != "") {

		editor.SetText(game.object_types[selected_type_name].script);

		editor.Render("editor");

		game.object_types[selected_type_name].script = editor.GetText();
	}

	ImGui::EndGroup();

	ImGui::End();
}