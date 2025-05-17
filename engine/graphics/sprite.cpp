#include "sprite.h"
#include <iostream>

Sprite::Sprite(unsigned int width, unsigned int height) {

	this->width  = width;
	this->height = height;

	this->sprite_buffer = std::vector<unsigned char>((this->width * 8) * (this->height * 8), 0);
}

Sprite::~Sprite() {}
