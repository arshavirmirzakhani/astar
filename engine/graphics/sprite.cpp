#include "sprite.h"
#include <iostream>

Sprite::Sprite() {
	this->width  = 1;
	this->height = 1;

	this->sprite_buffer = std::vector<unsigned char>((this->width * 8) * (this->height * 8), 0);
}
Sprite::Sprite(unsigned int width, unsigned int height) {

	this->width  = width;
	this->height = height;

	this->sprite_buffer = std::vector<unsigned char>((this->width * 8) * (this->height * 8), 0);
}

Sprite::~Sprite() {}

void Sprite::load_sprite_from_image(const Pallete pallete, unsigned char* data, bool is_rgba) {

	for (unsigned int y = 0; y < this->height * 8; y++) {
		for (unsigned int x = 0; x < this->width * 8; x++) {

			unsigned int index = y * this->width * 8 + x;

			unsigned int pixel_offset = index * 4;
			Color target		  = {data[pixel_offset], data[pixel_offset + 1], data[pixel_offset + 2],
					     (is_rgba) ? data[pixel_offset + 3] : (unsigned char)0};

			for (unsigned char i = 1; i < 128 + 1; i++) {

				if (i == 128) {
					this->sprite_buffer[index] = 0;
					break;
				}

				if (pallete.colors[i - 1].r == target.r && pallete.colors[i - 1].g == target.g &&
				    pallete.colors[i - 1].b == target.b && pallete.colors[i - 1].a == target.a) {
					this->sprite_buffer[index] = i - 1;
					break;
				}
			}
		}
	}
}
