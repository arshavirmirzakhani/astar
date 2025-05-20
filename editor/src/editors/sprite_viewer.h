#include "globals.h"
#include "imgui/ImGuiFileDialog.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>
#include <algorithm>
#include <engine/game.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>

static ImVec2 panOffset = ImVec2(0, 0);
static bool isPanning	= false;
static ImVec2 panStartMousePos;
static ImVec2 panStartOffset;
static unsigned int choosen_color_index	  = 0;
static unsigned int selected_sprite_index = 0;

std::string image_path	    = "";
std::string selected_sprite = "default";
SDL_Texture* preview_textue;
SDL_FRect rect;

static char new_sprite_name[256] = "";

ImVec4 toImVec4(unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a) {
	return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

void regenerate_sprite_from_image(Sprite& sprite, Pallete& pallete) {
	if (image_path.empty())
		return;

	int w, h, comp;
	unsigned char* image = stbi_load(image_path.c_str(), &w, &h, &comp, 0);

	if (!image) {
		std::cerr << "Failed to reload image: " << stbi_failure_reason() << std::endl;
		return;
	}

	if (w % 8 == 0 && h % 8 == 0) {
		Sprite new_sprite(w / 8, h / 8);
		new_sprite.load_sprite_from_image(pallete, image, comp == 4);
		sprite = new_sprite;

	} else {
		std::cerr << "Image dimensions not divisible by 8\n";
	}

	stbi_image_free(image);
}

std::string read_pallete_file(const std::string& filename) {
	std::ifstream file(filename);
	std::string output;
	std::string word;

	while (file >> word) {
		output.append(word);
		output.append(" ");
	}

	return output;
}

void show_sprite_viewer(Game& game, SDL_Renderer* renderer) {
	static float zoom     = 1.0f;
	static float prevZoom = zoom;
	const float minZoom   = 0.1f;
	const float maxZoom   = 100.0f;

	ImGui::Begin("sprite viewer");

	ImGui::BeginGroup();

	ImGui::Text("Sprites");

	if (ImGui::BeginPopup("New sprite")) {

		ImGui::InputText("sprite name", new_sprite_name, 255);

		if (game.sprites.find(new_sprite_name) != game.sprites.end()) {
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "a sprite with same name exist");
		}

		else if (ImGui::Button("create")) {
			game.sprites[new_sprite_name] = Sprite(1, 1);

			selected_sprite = new_sprite_name;

			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("cancel")) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	if (ImGui::BeginPopup("Rename sprite")) {

		ImGui::InputText("sprite name", new_sprite_name, 255);

		if (game.sprites.find(new_sprite_name) != game.sprites.end()) {
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "a sprite with same name exist");
		}

		else if (ImGui::Button("rename")) {

			auto handler = game.sprites.extract(selected_sprite);

			handler.key() = new_sprite_name;
			game.sprites.insert(std::move(handler));

			selected_sprite = new_sprite_name;

			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("cancel")) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	if (ImGui::Button("New")) {
		ImGui::OpenPopup("New sprite");
	}

	ImGui::SameLine();

	if (ImGui::Button("Delete")) {
		if (game.sprites.size() > 1) {
			game.sprites.erase(selected_sprite);
			selected_sprite = game.sprites.begin()->first;
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Rename")) {
		ImGui::OpenPopup("Rename sprite");
	}

	if (ImGui::BeginChild("sprites", ImVec2(250, 100), ImGuiChildFlags_AutoResizeY)) {
		int index = 0;
		for (auto& [name, sprite] : game.sprites) {
			bool is_selected = (selected_sprite_index == index);
			if (ImGui::Selectable(name.c_str(), is_selected)) {
				selected_sprite_index = index;
				selected_sprite	      = name;
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();

			++index;
		}
	}
	ImGui::EndChild();
	ImGui::EndGroup();

	ImGui::SameLine();

	// Palette preview
	ImGui::BeginGroup();

	if (ImGui::Button("Import image")) {
		ImGuiFileDialog::Instance()->OpenDialog("choose_file_dialog_image", "Choose sprite image",
							".png,.jpeg,.jpg,.gif", file_conf);
	}

	ImGui::SameLine();

	if (ImGui::Button("Import pallete")) {
		ImGuiFileDialog::Instance()->OpenDialog("choose_file_dialog_pallete", "Choose pallete", ".txt,.hex",
							file_conf);
	}

	if (ImGuiFileDialog::Instance()->Display("choose_file_dialog_image")) {
		if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();

			image_path = filePathName;

			regenerate_sprite_from_image(game.sprites[selected_sprite], game.pallete);
		}
		ImGuiFileDialog::Instance()->Close();
	}

	if (ImGuiFileDialog::Instance()->Display("choose_file_dialog_pallete")) {
		if (ImGuiFileDialog::Instance()->IsOk()) {
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
			std::string data	 = read_pallete_file(filePathName);

			// Load new palette
			game.pallete.load_pallete_from_hex(data);
		}

		ImGuiFileDialog::Instance()->Close();
	}

	ImGui::Text("Palette");

	for (unsigned int i = 0; i < 127; ++i) {
		ImGui::PushID(i);
		if (ImGui::ColorButton("##color",
				       toImVec4(game.pallete.colors[i].r, game.pallete.colors[i].g,
						game.pallete.colors[i].b, game.pallete.colors[i].a),
				       0, ImVec2(30, 30))) {

			choosen_color_index = i;
		};
		ImGui::PopID();

		if ((i + 1) % 8 != 0)
			ImGui::SameLine();
	}

	ImGui::NewLine();

	float color[4] = {
	    game.pallete.colors[choosen_color_index].r / 255.0f, game.pallete.colors[choosen_color_index].g / 255.0f,
	    game.pallete.colors[choosen_color_index].b / 255.0f, game.pallete.colors[choosen_color_index].a / 255.0f};

	if (ImGui::ColorEdit4("Color Editor", color,
			      ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar |
				  ImGuiColorEditFlags_AlphaPreview)) {
		game.pallete.colors[choosen_color_index].r = static_cast<unsigned char>(color[0] * 255.0f);
		game.pallete.colors[choosen_color_index].g = static_cast<unsigned char>(color[1] * 255.0f);
		game.pallete.colors[choosen_color_index].b = static_cast<unsigned char>(color[2] * 255.0f);
		game.pallete.colors[choosen_color_index].a = static_cast<unsigned char>(color[3] * 255.0f);
	}

	ImGui::SetNextItemWidth(200);

	ImGui::EndGroup();
	ImGui::SameLine();

	// === Render Sprite ===

	if (preview_textue) {
		SDL_DestroyTexture(preview_textue);
		preview_textue = nullptr;
	}

	preview_textue = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
					   (int)(game.sprites[selected_sprite].width * 8),
					   (int)(game.sprites[selected_sprite].height * 8));

	SDL_SetTextureScaleMode(preview_textue, SDL_SCALEMODE_NEAREST);
	SDL_SetTextureBlendMode(preview_textue, SDL_BLENDMODE_BLEND);

	SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, preview_textue);

	for (unsigned int y = 0; y < game.sprites[selected_sprite].height * 8; y++) {
		for (unsigned int x = 0; x < game.sprites[selected_sprite].width * 8; x++) {
			if (game.sprites[selected_sprite]
				.sprite_buffer[y * game.sprites[selected_sprite].width * 8 + x] == 0) {
				continue;
			} else {
				Color color =
				    game.pallete
					.colors[game.sprites[selected_sprite]
						    .sprite_buffer[y * game.sprites[selected_sprite].width * 8 + x]];
				if (color.a == 0)
					continue;

				SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			}

			rect = {(float)x, (float)y, 1, 1};
			SDL_RenderFillRect(renderer, &rect);
		}
	}

	SDL_SetRenderTarget(renderer, oldTarget);

	// === Sprite Viewer UI ===
	ImGui::BeginGroup();
	ImGui::Text("zoom");
	ImGui::VSliderFloat("##ZoomSlider", ImVec2(40, 200), &zoom, minZoom, maxZoom, "%.1fx",
			    ImGuiSliderFlags_Logarithmic);
	ImGui::EndGroup();

	ImGui::SameLine();

	ImVec2 childSize = ImGui::GetContentRegionAvail();
	ImGui::BeginChild("SpriteView", childSize, true,
			  ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

	ImVec2 canvasPos  = ImGui::GetCursorScreenPos();    // Top-left of the child
	ImVec2 canvasSize = ImGui::GetContentRegionAvail(); // Size of the drawable area

	// Handle mouse wheel zoom
	float wheel = ImGui::GetIO().MouseWheel;
	if (wheel != 0.0f && ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows)) {
		prevZoom = zoom;
		zoom *= (wheel > 0) ? 1.1f : 0.9f;
		zoom = std::clamp(zoom, minZoom, maxZoom);

		// Zoom from center
		ImVec2 canvasCenter = ImVec2(canvasSize.x * 0.5f, canvasSize.y * 0.5f);
		float zoomFactor    = zoom / prevZoom;
		panOffset.x	    = canvasCenter.x + (panOffset.x - canvasCenter.x) * zoomFactor;
		panOffset.y	    = canvasCenter.y + (panOffset.y - canvasCenter.y) * zoomFactor;
	}

	// Panning logic
	ImGui::InvisibleButton("canvas", canvasSize, ImGuiButtonFlags_MouseButtonLeft);
	if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
		ImVec2 dragDelta = ImGui::GetIO().MouseDelta;
		panOffset.x += dragDelta.x;
		panOffset.y += dragDelta.y;
	}

	// Draw sprite texture
	ImVec2 spriteSize =
	    ImVec2(zoom * game.sprites[selected_sprite].width * 8, zoom * game.sprites[selected_sprite].height * 8);
	ImVec2 imagePos = ImVec2(canvasPos.x + panOffset.x, canvasPos.y + panOffset.y);

	ImGui::GetWindowDrawList()->AddImage((ImTextureID)preview_textue, imagePos,
					     ImVec2(imagePos.x + spriteSize.x, imagePos.y + spriteSize.y));

	ImGui::EndChild();
	ImGui::End();
}
