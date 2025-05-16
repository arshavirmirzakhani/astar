#include "sprite.h"
#include <iostream>

Sprite::Sprite(unsigned int width, unsigned int height) {

	this->width  = width;
	this->height = height;

	this->sprite_buffer = std::vector<unsigned char>((this->width * 8) * (this->height * 8), 0);
}

Sprite::~Sprite() {}

unsigned char* Sprite::render(int sprite_Xy, int sprite_y) {

	std::vector<unsigned char> buffer;

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			if (x >= sprite_Xy && x <= sprite_Xy + this->width && y >= sprite_y &&
			    y <= sprite_y + this->height) {
				buffer.push_back(this->sprite_buffer[(y * width) + x]);
			}
		}
	}

	return buffer.data();
}
