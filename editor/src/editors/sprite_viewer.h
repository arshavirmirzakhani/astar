#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>
#include <algorithm>
#include <engine/game.h>
#include <stdio.h>
#include <string>

static ImVec2 panOffset = ImVec2(0, 0);
static bool isPanning	= false;
static ImVec2 panStartMousePos;
static ImVec2 panStartOffset;

SDL_Texture* preview_textue;

ImVec4 toImVec4(unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a) {
	return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

void show_sprite_viewer(SDL_Renderer* renderer, Sprite& sprite, Pallete& pallete, unsigned int& choosen_color_index) {
	static float zoom   = 1.0f;
	const float minZoom = 0.1f;
	const float maxZoom = 100.0f;

	zoom = std::clamp(zoom, minZoom, maxZoom);

	ImGui::Begin("sprite viewer");

	// Palette preview
	ImGui::BeginGroup();
	ImGui::Text("Palette");

	for (unsigned int i = 0; i < 127; ++i) {
		ImGui::PushID(i);
		ImGui::ColorButton(
		    "##color",
		    toImVec4(pallete.colors[i].r, pallete.colors[i].g, pallete.colors[i].b, pallete.colors[i].a), 0,
		    ImVec2(30, 30));
		ImGui::PopID();

		if ((i + 1) % 8 != 0)
			ImGui::SameLine();
	}

	ImGui::NewLine();

	Color& c	     = pallete.colors[choosen_color_index];
	ImVec4 editableColor = toImVec4(c.r, c.g, c.b, c.a);
	ImGui::ColorEdit4("Color Editor", (float*)&editableColor,
			  ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar |
			      ImGuiColorEditFlags_AlphaPreview);

	ImGui::EndGroup();
	ImGui::SameLine();

	// === Render Sprite ===

	preview_textue = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
					   sprite.width * 8, sprite.height * 8);

	SDL_SetTextureBlendMode(preview_textue, SDL_BLENDMODE_BLEND);

	SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);

	SDL_SetRenderTarget(renderer, preview_textue);

	// Clear the texture to a color (e.g., greenish)
	SDL_SetRenderDrawColor(renderer, 30, 200, 150, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderTarget(renderer, oldTarget);

	// === Sprite Viewer ===
	ImGui::BeginGroup();
	ImGui::Text("zoom");
	ImGui::VSliderFloat("##ZoomSlider", ImVec2(40, 200), &zoom, minZoom, maxZoom, "%.1fx");
	ImGui::EndGroup();

	ImGui::SameLine();

	// Size of the scrollable/interactive area
	ImVec2 childSize = ImGui::GetContentRegionAvail();
	ImGui::BeginChild("SpriteView", childSize, true,
			  ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

	ImVec2 canvasPos  = ImGui::GetCursorScreenPos();    // Top-left of the child
	ImVec2 canvasSize = ImGui::GetContentRegionAvail(); // Size of the drawable area

	ImGui::InvisibleButton("canvas", canvasSize, ImGuiButtonFlags_MouseButtonLeft);

	// Handle panning with mouse drag
	if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
		ImVec2 dragDelta = ImGui::GetIO().MouseDelta;
		panOffset.x += dragDelta.x;
		panOffset.y += dragDelta.y;
	}

	// Draw the image at the pan offset
	ImVec2 spriteSize = ImVec2(zoom * sprite.width * 8, zoom * sprite.height * 8);
	ImVec2 imagePos	  = ImVec2(canvasPos.x + panOffset.x, canvasPos.y + panOffset.y);

	ImGui::GetWindowDrawList()->AddImage((ImTextureID)preview_textue, imagePos,
					     ImVec2(imagePos.x + spriteSize.x, imagePos.y + spriteSize.y));

	ImGui::EndChild();

	ImGui::End(); // window
}
