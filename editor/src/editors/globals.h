#pragma once

#include "imgui/ImGuiFileDialog.h"

#define STB_IMAGE_IMPLEMENTATION
#include "engine/game.h"
#include <SDL.h>
#include <stb_image.h>

IGFD::FileDialogConfig file_conf;

IGFD::FileDialogConfig file_save_conf;

void regenerate_sprite_from_image(std::string image_path, Sprite& sprite, Pallete& pallete) {
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