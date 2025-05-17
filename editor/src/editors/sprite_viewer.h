#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>
#include <algorithm>
#include <engine/game.h>
#include <stdio.h>
#include <string>

ImVec4 toImVec4(unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a) {
	return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

void show_sprite_viewer(Sprite& sprite, Pallete& pallete, unsigned int& choosen_color_index) {
	static float zoom   = 1.0f;
	const float minZoom = 0.25f;
	const float maxZoom = 10.0f;

	ImGui::Begin("sprite_editor");

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

	// === Sprite Viewer ===
	ImGui::BeginGroup();

	ImGuiStyle& style      = ImGui::GetStyle();
	ImVec2 oldItemSpacing  = style.ItemSpacing;
	ImVec2 oldFramePadding = style.FramePadding;

	style.ItemSpacing  = ImVec2(0, 0);
	style.FramePadding = ImVec2(0, 0);

	// Vertical zoom slider
	ImGui::BeginGroup();
	ImGui::VSliderFloat("##ZoomSlider", ImVec2(20, 200), &zoom, minZoom, maxZoom, "%.1fx");
	ImGui::EndGroup();
	ImGui::SameLine();

	// Canvas
	unsigned int gridWidth	= sprite.width * 8;
	unsigned int gridHeight = sprite.height * 8;
	float pixelSize		= 16.0f * zoom;
	ImVec2 canvasSize	= ImVec2(gridWidth * pixelSize, gridHeight * pixelSize);

	ImGui::BeginChild("CanvasRegion", ImVec2(0, 0), true,
			  ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 origin	     = ImGui::GetCursorScreenPos();

	for (unsigned int y = 0; y < gridHeight; ++y) {
		for (unsigned int x = 0; x < gridWidth; ++x) {
			unsigned int index	 = y * gridWidth + x;
			unsigned int color_index = sprite.sprite_buffer[index];

			ImVec2 cellMin = ImVec2(origin.x + x * pixelSize, origin.y + y * pixelSize);
			ImVec2 cellMax = ImVec2(cellMin.x + pixelSize, cellMin.y + pixelSize);

			// Transparent background (checkerboard)
			int checkerSize = static_cast<int>(pixelSize / 2);
			for (int cy = 0; cy < 2; ++cy) {
				for (int cx = 0; cx < 2; ++cx) {
					ImVec2 p0 = ImVec2(cellMin.x + cx * checkerSize, cellMin.y + cy * checkerSize);
					ImVec2 p1 = ImVec2(p0.x + checkerSize, p0.y + checkerSize);
					ImU32 checkerColor = ((cx + cy) % 2 == 0) ? IM_COL32(200, 200, 200, 255)
										  : IM_COL32(150, 150, 150, 255);
					drawList->AddRectFilled(p0, p1, checkerColor);
				}
			}

			if (color_index > 0 && color_index < 128) {
				Color color = pallete.colors[color_index - 1];
				drawList->AddRectFilled(cellMin, cellMax,
							ImColor(toImVec4(color.r, color.g, color.b, color.a)));
			}

			drawList->AddRect(cellMin, cellMax, IM_COL32(60, 60, 60, 255)); // cell border
		}
	}

	ImGui::EndChild();

	style.ItemSpacing  = oldItemSpacing;
	style.FramePadding = oldFramePadding;

	ImGui::EndGroup(); // sprite viewer group
	ImGui::End();	   // window
}
