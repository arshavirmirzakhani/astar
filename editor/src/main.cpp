#ifdef __EMSCRIPTEN__
#include <SDL.h>
#else
#include <SDL3/SDL.h>
#endif

#include "editors/globals.h"
#include "editors/object_editor.h"
#include "editors/scene_editor.h"
#include "editors/script_editor.h"
#include "editors/settings_editor.h"
#include "editors/sprite_viewer.h"
#include "font.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include "imgui_theme_setup.h"
#include <cereal/archives/binary.hpp>
#include <engine/game.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

static bool is_open_sprite_viewer;
static bool is_open_object_editor;
static bool is_open_scene_editor;
static bool is_open_script_editor;
static bool is_open_settings_editor;

static char new_project_name[255] = "";

// Main code
int main(int, char**) {

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
		printf("Error: SDL_Init(): %s\n", SDL_GetError());
		return -1;
	}

	// Create window with SDL_Renderer graphics context
	SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
	SDL_Window* window	     = SDL_CreateWindow("Astar editor", 1280, 720, window_flags);
	if (window == nullptr) {
		printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
	SDL_SetRenderVSync(renderer, 1);
	if (renderer == nullptr) {
		SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
		return -1;
	}

	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_ShowWindow(window);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
	io.ConfigWindowsMoveFromTitleBarOnly = true;

	ImFontConfig font_config;
	font_config.FontDataOwnedByAtlas = false;

	ImFont* font = io.Fonts->AddFontFromMemoryTTF((void*)font_data, font_size, 20.0f, &font_config);
	//  Setup Dear ImGui style
	SetupImGuiStyle();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool done	   = false;

	// ======
	static SDL_Texture* sprite_viewer_texture = nullptr;
	Game game("New game");
	game.pallete.load_pallete_from_hex(aap_64);
	// ======

	file_conf.path = ".";

	file_save_conf.path		 = ".";
	file_save_conf.fileName		 = "project.astar";
	file_save_conf.countSelectionMax = 1;
	file_save_conf.flags		 = ImGuiFileDialogFlags_ConfirmOverwrite;

	TextEditor code_editor;

	code_editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
	code_editor.SetText("");
	code_editor.SetShowWhitespaces(false);
	code_editor.SetShowShortTabGlyphs(true);

	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT)
				done = true;
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
				done = true;
		}

		if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
			SDL_Delay(10);
			continue;
		}

		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();

		ImGui::NewFrame();

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
						ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus |
						ImGuiWindowFlags_NoNavFocus;

		if (ImGui::Begin("BaseWindow", nullptr, window_flags)) {
			ImGuiID dockspace_id = ImGui::GetID("MainDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

			ImGui::Begin("Editors");
			ImGui::Text("A-STAR engine editor");
			ImGui::Text("by Arshavir Mirzakhani");

			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), std::string("Editing project: " + game.name).c_str());
			ImGui::SeparatorText("Project");

			if (ImGui::Button("New")) {
				ImGui::OpenPopup("New project");
			}

			if (ImGui::BeginPopup("New project")) {

				ImGui::InputText("sprite name", new_project_name, 255);

				if (strlen(new_project_name) == 0) {
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "project name is required");
				}

				else if (ImGui::Button("create")) {
					game = Game(new_project_name);
					game.pallete.load_pallete_from_hex(aap_64);

					selected_sprite = game.sprites.begin()->first;

					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();
				if (ImGui::Button("cancel")) {
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			if (ImGui::Button("Open")) {
				ImGuiFileDialog::Instance()->OpenDialog("choose_file_dialog_project_file", "Choose project file", ".astar", file_conf);
			}

			if (ImGuiFileDialog::Instance()->Display("choose_file_dialog_project_file")) {
				if (ImGuiFileDialog::Instance()->IsOk()) {
					std::ifstream file(ImGuiFileDialog::Instance()->GetFilePathName(), std::ios::binary);

					cereal::BinaryInputArchive iarchive(file);

					iarchive(game);

					selected_sprite = game.sprites.begin()->first;
				}
				ImGuiFileDialog::Instance()->Close();
			}
			if (ImGui::Button("Save as")) {

				ImGuiFileDialog::Instance()->OpenDialog("save_project_file_dialog", "Save", ".astar", file_conf);
			}

			if (ImGuiFileDialog::Instance()->Display("save_project_file_dialog")) {
				if (ImGuiFileDialog::Instance()->IsOk()) {
					std::ofstream file(ImGuiFileDialog::Instance()->GetFilePathName(), std::ios::binary);

					cereal::BinaryOutputArchive oarchive(file);

					oarchive(game);
				}
				ImGuiFileDialog::Instance()->Close();
			}

			ImGui::SeparatorText("Editors");

			if (ImGui::Button("Edit project settings")) {
				is_open_settings_editor = (is_open_settings_editor) ? false : true;
			}

			if (ImGui::Button("View sprites")) {
				is_open_sprite_viewer = (is_open_sprite_viewer) ? false : true;
			}

			if (ImGui::Button("Edit Objects")) {
				is_open_object_editor = (is_open_object_editor) ? false : true;
			}

			if (ImGui::Button("Edit scripts")) {
				is_open_script_editor = (is_open_script_editor) ? false : true;
			}

			if (ImGui::Button("Edit scenes")) {
				is_open_scene_editor = (is_open_scene_editor) ? false : true;
			}

			ImGui::End();

			if (is_open_settings_editor) {
				show_settings_editor(game);
			}

			if (is_open_sprite_viewer) {
				show_sprite_viewer(game, renderer);
			}

			if (is_open_object_editor) {
				show_object_editor(game, renderer);
			}

			if (is_open_script_editor) {
				show_script_editor(game, code_editor);
			}

			if (is_open_scene_editor) {
				show_scene_editor(game, renderer);
			}
		}
		ImGui::End();

		// Rendering
		ImGui::Render();

		SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		SDL_RenderClear(renderer);
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
		SDL_RenderPresent(renderer);
	}

	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();

	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
