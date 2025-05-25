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

static ImVec2 panOffset			  = ImVec2(0, 0);
static unsigned int choosen_color_index	  = 0;
static unsigned int selected_sprite_index = 0;

std::string image_path	    = "";
std::string selected_sprite = "default";
SDL_Texture* preview_textue = nullptr;
SDL_FRect rect;
static char new_sprite_name[255] = "";

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
	std::string output, word;
	while (file >> word) {
		output.append(word + " ");
	}
	return output;
}

void show_sprite_viewer(Game& game, SDL_Renderer* renderer) {
	static float zoom     = 1.0f;
	static float prevZoom = zoom;
	const float minZoom = 0.1f, maxZoom = 100.0f;

	ImGui::Begin("Sprite Viewer");

	// === Sprite Management Panel ===
	ImGui::BeginGroup();
	ImGui::Text("Sprites");

	if (ImGui::Button("New"))
		ImGui::OpenPopup("New sprite");
	ImGui::SameLine();
	if (ImGui::Button("Rename"))
		ImGui::OpenPopup("Rename sprite");
	ImGui::SameLine();
	if (ImGui::Button("Delete")) {
		if (game.sprites.size() > 1) {
			game.sprites.erase(selected_sprite);
			selected_sprite = game.sprites.begin()->first;
		}
	}

	// New Sprite Popup
	if (ImGui::BeginPopup("New sprite")) {
		ImGui::InputText("Sprite name", new_sprite_name, 255);
		if (game.sprites.find(new_sprite_name) != game.sprites.end()) {
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "Sprite already exists");
		} else if (ImGui::Button("Create")) {
			game.sprites[new_sprite_name] = Sprite(1, 1);
			selected_sprite		      = new_sprite_name;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}

	// Rename Sprite Popup
	if (ImGui::BeginPopup("Rename sprite")) {
		ImGui::InputText("New name", new_sprite_name, 255);
		if (game.sprites.find(new_sprite_name) != game.sprites.end()) {
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "Name already taken");
		} else if (ImGui::Button("Rename")) {
			auto node  = game.sprites.extract(selected_sprite);
			node.key() = new_sprite_name;
			game.sprites.insert(std::move(node));
			selected_sprite = new_sprite_name;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}

	// Sprite List
	if (ImGui::BeginChild("SpriteList", ImVec2(200, 150), true)) {
		int index = 0;
		for (const auto& [name, sprite] : game.sprites) {
			bool selected = (selected_sprite_index == index);
			if (ImGui::Selectable(name.c_str(), selected)) {
				selected_sprite_index = index;
				selected_sprite	      = name;
			}
			if (selected)
				ImGui::SetItemDefaultFocus();
			++index;
		}
	}
	ImGui::EndChild();
	ImGui::EndGroup();

	// === Palette + File Import ===
	ImGui::SameLine();
	ImGui::BeginGroup();
	ImGui::Text("Image / Palette");

	if (ImGui::Button("Import Image")) {
		ImGuiFileDialog::Instance()->OpenDialog("choose_file_dialog_image", "Choose sprite image",
							".png,.jpg,.gif", file_conf);
	}
	ImGui::SameLine();
	if (ImGui::Button("Import Palette")) {
		ImGuiFileDialog::Instance()->OpenDialog("choose_file_dialog_palette", "Choose palette", ".txt,.hex",
							file_conf);
	}

	if (ImGuiFileDialog::Instance()->Display("choose_file_dialog_image")) {
		if (ImGuiFileDialog::Instance()->IsOk()) {
			image_path = ImGuiFileDialog::Instance()->GetFilePathName();
			regenerate_sprite_from_image(game.sprites[selected_sprite], game.pallete);
		}
		ImGuiFileDialog::Instance()->Close();
	}
	if (ImGuiFileDialog::Instance()->Display("choose_file_dialog_palette")) {
		if (ImGuiFileDialog::Instance()->IsOk()) {
			std::string path = ImGuiFileDialog::Instance()->GetFilePathName();
			game.pallete.load_pallete_from_hex(read_pallete_file(path));

			game.sprites[selected_sprite].regenerate_with_current_palette(
			    game.pallete, game.sprites[selected_sprite].original_has_alpha);
		}
		ImGuiFileDialog::Instance()->Close();
	}

	ImGui::Text("Palette");
	for (unsigned int i = 0; i < 128; ++i) {
		ImGui::PushID(i);
		if (ImGui::ColorButton("##color",
				       toImVec4(game.pallete.colors[i].r, game.pallete.colors[i].g,
						game.pallete.colors[i].b, game.pallete.colors[i].a),
				       0, ImVec2(30, 30))) {
			choosen_color_index = i;
		}
		ImGui::PopID();
		if ((i + 1) % 8 != 0)
			ImGui::SameLine();
	}

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

	ImGui::EndGroup();

	// === Sprite Zoom View ===
	ImGui::SameLine();
	ImGui::BeginGroup();
	ImGui::Text("Zoom");
	ImGui::VSliderFloat("##ZoomSlider", ImVec2(40, 200), &zoom, minZoom, maxZoom, "%.1fx",
			    ImGuiSliderFlags_Logarithmic);
	ImGui::EndGroup();

	ImGui::SameLine();

	ImVec2 canvasSize = ImGui::GetContentRegionAvail();
	ImGui::BeginChild("SpriteCanvas", canvasSize, true,
			  ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

	ImVec2 canvasPos = ImGui::GetCursorScreenPos();
	if (canvasSize.x <= 0 || canvasSize.y <= 0) {
		ImGui::EndChild();
		ImGui::End();
		return;
	}

	// Zoom center
	float wheel = ImGui::GetIO().MouseWheel;
	if (wheel != 0.0f && ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows)) {
		prevZoom = zoom;
		zoom *= (wheel > 0) ? 1.1f : 0.9f;
		zoom	      = std::clamp(zoom, minZoom, maxZoom);
		ImVec2 center = ImVec2(canvasSize.x * 0.5f, canvasSize.y * 0.5f);
		float factor  = zoom / prevZoom;
		panOffset.x   = center.x + (panOffset.x - center.x) * factor;
		panOffset.y   = center.y + (panOffset.y - center.y) * factor;
	}

	// Drag/Pan
	ImGui::InvisibleButton("canvas", canvasSize, ImGuiButtonFlags_MouseButtonLeft);
	if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
		ImVec2 delta = ImGui::GetIO().MouseDelta;
		panOffset.x += delta.x;
		panOffset.y += delta.y;
	}

	// Render to preview texture
	if (preview_textue)
		SDL_DestroyTexture(preview_textue);
	preview_textue =
	    SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			      game.sprites[selected_sprite].width * 8, game.sprites[selected_sprite].height * 8);
	SDL_SetTextureScaleMode(preview_textue, SDL_SCALEMODE_NEAREST);
	SDL_SetTextureBlendMode(preview_textue, SDL_BLENDMODE_BLEND);

	SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, preview_textue);

	for (unsigned int y = 0; y < game.sprites[selected_sprite].height * 8; y++) {
		for (unsigned int x = 0; x < game.sprites[selected_sprite].width * 8; x++) {
			uint8_t pixel = game.sprites[selected_sprite]
					    .sprite_buffer[y * game.sprites[selected_sprite].width * 8 + x];
			if (pixel == 0)
				continue;

			Color color = game.pallete.colors[pixel];
			if (color.a == 0)
				continue;

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			rect = {(float)x, (float)y, 1, 1};
			SDL_RenderFillRect(renderer, &rect);
		}
	}

	SDL_SetRenderTarget(renderer, oldTarget);

	// Draw image on canvas
	ImVec2 imageSize = {zoom * game.sprites[selected_sprite].width * 8,
			    zoom * game.sprites[selected_sprite].height * 8};
	ImVec2 imagePos	 = ImVec2(canvasPos.x + panOffset.x, canvasPos.y + panOffset.y);

	ImGui::GetWindowDrawList()->AddImage((ImTextureID)preview_textue, imagePos,
					     ImVec2(imagePos.x + imageSize.x, imagePos.y + imageSize.y));
	ImGui::EndChild();

	ImGui::End();
}
