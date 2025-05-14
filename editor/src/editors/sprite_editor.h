#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include "imgui/imgui.h"
#include <stdio.h>
#include <string>
#include <SDL3/SDL.h>
#include <engine/game.h>

ImVec4 toImVec4(unsigned char r,unsigned char g,unsigned char b,unsigned char a) {
    return ImVec4(
        r / 255.0f,
        g / 255.0f,
        b / 255.0f,
        a / 255.0f
    );
}

void show_sprite_editor(Sprite& sprite, Pallete& pallete) {

    ImGui::Begin("sprite_editor");
    
    ImGui::Text("pallete");
    for (int i = 0; i < 127; ++i) {
        
        ImGui::PushID(i);
        if (ImGui::ColorButton("##color", toImVec4(pallete.colors[i].r,pallete.colors[i].g,pallete.colors[i].b,pallete.colors[i].a),0,ImVec2(40,40))) {
    
        }

        if ((i + 1) % 8 != 0) {
            ImGui::SameLine();
        } 
                
        ImGui::PopID();
    }

    ImGui::End();

}