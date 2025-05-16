#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include "imgui/imgui.h"
#include <stdio.h>
#include <string>
#include <SDL3/SDL.h>
#include <engine/game.h>

ImVec4 toImVec4(unsigned char& r,unsigned char& g,unsigned char& b,unsigned char& a) {
    return ImVec4(
        r / 255.0f,
        g / 255.0f,
        b / 255.0f,
        a / 255.0f
    );
}

void show_sprite_editor(Sprite& sprite, Pallete& pallete,unsigned int& choosen_color_index) {
    
    ImGui::Begin("sprite_editor");
   
    
    ImGui::BeginGroup();
    ImGui::Text("pallete");

    for (unsigned int i = 0; i < 127; ++i) {
        
        ImGui::PushID(i);
        if (ImGui::ColorButton("##color", toImVec4(pallete.colors[i].r,pallete.colors[i].g,pallete.colors[i].b,pallete.colors[i].a),0,ImVec2(20,20))) {
            choosen_color_index = i;
        }
        
        if ((i + 1) % 8 != 0) {
            ImGui::SameLine();
        } 
        
        ImGui::PopID();
    }

    ImGui::NewLine();

    Color& c = pallete.colors[choosen_color_index];
    ImVec4 editableColor = toImVec4(c.r, c.g, c.b, c.a);

    if (ImGui::ColorEdit4("color editor", (float*)&editableColor,ImGuiColorEditFlags_NoInputs)) {
        // Convert float [0,1] back to byte [0,255]
        c.r = static_cast<unsigned char>(editableColor.x * 255);
        c.g = static_cast<unsigned char>(editableColor.y * 255);
        c.b = static_cast<unsigned char>(editableColor.z * 255);
        c.a = static_cast<unsigned char>(editableColor.w * 255);
    }

    ImGui::EndGroup();
    
    
    ImGui::SameLine();
    
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    float cellSize = 50.0f;
    ImVec2 origin = ImGui::GetCursorScreenPos();

    
    for (unsigned int y = 0; y < sprite.height*8; y++) {
        for (unsigned int x = 0; x < sprite.width*8; x++) {

            ImVec2 cellMin = ImVec2(origin.x + x * cellSize, origin.y + y * cellSize);
            ImVec2 cellMax = ImVec2(cellMin.x + cellSize, cellMin.y + cellSize);

            unsigned int color_index = (unsigned int)(sprite.sprite_buffer[(y * (sprite.width * 8)) + x + 1]);

            if (color_index < 0 || color_index >= 127)
                continue;

            Color color = pallete.colors[color_index];
            
            ImU32 col = ImColor(toImVec4(color.r,color.g,color.b,color.a));
            drawList->AddRectFilled(cellMin, cellMax, col);
            drawList->AddRect(cellMin, cellMax, IM_COL32(50, 50, 50, 255));
            
            
            // Handle click
            if (ImGui::IsMouseHoveringRect(cellMin, cellMax) && ImGui::IsMouseDown(0)) {
                sprite.sprite_buffer[(y * (sprite.width*8)) + x] = choosen_color_index - 1;
            }
            
        }
    }

    ImGui::Dummy(ImVec2(sprite.width * cellSize, sprite.height * cellSize));


    ImGui::End();

}