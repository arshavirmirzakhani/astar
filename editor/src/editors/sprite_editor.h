#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>
#include <engine/game.h>
#include <stdio.h>
#include <string>

ImVec4 toImVec4(unsigned char &r, unsigned char &g, unsigned char &b,
                unsigned char &a) {
  return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

void show_sprite_editor(Sprite &sprite, Pallete &pallete,
                        unsigned int &choosen_color_index) {

  ImGui::Begin("sprite_editor");

  ImGui::BeginGroup();
  ImGui::Text("pallete");

  for (unsigned int i = 0; i < 127; ++i) {

    ImGui::PushID(i);
    if (ImGui::ColorButton("##color",
                           toImVec4(pallete.colors[i].r, pallete.colors[i].g,
                                    pallete.colors[i].b, pallete.colors[i].a),
                           0, ImVec2(40, 40))) {
      choosen_color_index = i;
    }
    ImGui::PopID();

    if ((i + 1) % 8 != 0) {
      ImGui::SameLine();
    }
  }

  ImGui::NewLine();

  Color &c = pallete.colors[choosen_color_index];
  ImVec4 editableColor = toImVec4(c.r, c.g, c.b, c.a);

  if (ImGui::ColorEdit4("color editor", (float *)&editableColor,
                        ImGuiColorEditFlags_NoInputs |
                            ImGuiColorEditFlags_AlphaBar |
                            ImGuiColorEditFlags_AlphaPreview)) {
    // Convert float [0,1] back to byte [0,255]
    c.r = static_cast<unsigned char>(editableColor.x * 255);
    c.g = static_cast<unsigned char>(editableColor.y * 255);
    c.b = static_cast<unsigned char>(editableColor.z * 255);
    c.a = static_cast<unsigned char>(editableColor.w * 255);
  }

  ImGui::EndGroup();

  ImGui::SameLine();

  ImGui::BeginGroup();

  ImGuiStyle &style = ImGui::GetStyle();
  ImVec2 oldItemSpacing = style.ItemSpacing;
  ImVec2 oldFramePadding = style.FramePadding;

  style.ItemSpacing = ImVec2(0, 0);
  style.FramePadding = ImVec2(0, 0);

  ImVec2 avail = ImGui::GetContentRegionAvail();
  int gridWidth = sprite.width * 8;
  int gridHeight = sprite.height * 8;

  float maxGridWidth = avail.x;
  float maxGridHeight = avail.y;

  float pixelSizeX = maxGridWidth / gridWidth;
  float pixelSizeY = maxGridHeight / gridHeight;
  float pixelSize = std::min(pixelSizeX, pixelSizeY); // keep square aspect

  ImVec2 canvasSize = ImVec2(pixelSize * gridWidth, pixelSize * gridHeight);
  ImGui::InvisibleButton("invcanvas", canvasSize, ImGuiButtonFlags_None);
  ImVec2 startPos = ImGui::GetItemRectMin();
  for (unsigned int y = 0; y < sprite.height * 8; y++) {
    for (unsigned int x = 0; x < sprite.width * 8; x++) {
      unsigned int index = y * (sprite.width * 8) + x;
      unsigned int color_index = sprite.sprite_buffer[index];
      if (color_index >= 128)
        continue;

      ImVec2 pos =
          ImVec2(startPos.x + x * pixelSize, startPos.y + y * pixelSize);

      ImDrawList *drawList = ImGui::GetWindowDrawList();

      ImVec2 cellMin = pos;
      ImVec2 cellMax = ImVec2(pos.x + pixelSize, pos.y + pixelSize);

      if (color_index == 0) {
        // Draw checkerboard for transparency
        int checkerSize = static_cast<int>(pixelSize / 2);
        for (int cy = 0; cy < 2; ++cy) {
          for (int cx = 0; cx < 2; ++cx) {
            ImVec2 p0 = ImVec2(cellMin.x + cx * checkerSize,
                               cellMin.y + cy * checkerSize);
            ImVec2 p1 = ImVec2(p0.x + checkerSize, p0.y + checkerSize);
            ImU32 checkerColor = ((cx + cy) % 2 == 0)
                                     ? IM_COL32(200, 200, 200, 255)
                                     : IM_COL32(150, 150, 150, 255);
            drawList->AddRectFilled(p0, p1, checkerColor);
          }
        }
      } else {
        Color color = pallete.colors[color_index - 1];
        ImU32 col = ImColor(toImVec4(color.r, color.g, color.b, color.a));
        drawList->AddRectFilled(cellMin, cellMax, col);
      }

      // drawList->AddRect(cellMin, cellMax, IM_COL32(50, 50, 50, 255)); //
      // border

      // Painting logic (click or drag)
      if (ImGui::IsMouseDown(ImGuiMouseButton_Left) &&
          ImGui::IsMouseHoveringRect(cellMin, cellMax)) {
        sprite.sprite_buffer[index] = choosen_color_index + 1;
      } else if (ImGui::IsMouseDown(ImGuiMouseButton_Right) &&
                 ImGui::IsMouseHoveringRect(cellMin, cellMax)) {
        sprite.sprite_buffer[index] = 0; // 0 = empty
      }
    }
  }

  // Restore styles
  style.ItemSpacing = oldItemSpacing;
  style.FramePadding = oldFramePadding;

  ImGui::EndGroup();

  ImGui::End();
}