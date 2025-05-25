#pragma once
#include "engine/game.h"
#include "imgui/TextEditor.h"
#include "imgui/imgui.h"

static TextEditor editor;
static std::string text		   = "main";
static int selected_script_index   = NULL;
static std::string selected_script = "";

static char new_object_type_name[255];

void show_script_editor(Game& game) {

	ImGui::Begin("Script editor");

	if (ImGui::Button("New")) {
		ImGui::OpenPopup("New object type");
	}

	if (ImGui::BeginPopup("New object type")) {

		ImGui::InputText("new object name", new_object_type_name, 255);

		if (game.sprites.find(new_object_type_name) != game.sprites.end()) {
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "a sprite with same name exist");
		}

		else if (ImGui::Button("create")) {
			game.object_types[new_object_type_name] = ObjectType();

			selected_script = new_object_type_name;

			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("cancel")) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	ImGui::BeginGroup();
	if (ImGui::BeginChild("object types", ImVec2(250, 100), ImGuiChildFlags_AutoResizeY)) {

		if (game.object_types.size() == 0) {
			selected_script_index = NULL;
		} else {
			int index = 0;
			for (auto& [name, type] : game.object_types) {
				bool is_selected = (selected_script_index == index);
				if (ImGui::Selectable(name.c_str(), is_selected)) {
					selected_script_index = index;
					selected_script	      = name;
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus();
				editor.SetText(type.script);

				++index;
			}
		}
	}
	ImGui::EndChild();
	ImGui::EndGroup();

	ImGui::SameLine();

	ImGui::BeginGroup();

	if (selected_script_index != NULL) {

		editor.Render("editor");

		game.object_types[selected_script].script = editor.GetText();
	}

	ImGui::EndGroup();

	ImGui::End();
}