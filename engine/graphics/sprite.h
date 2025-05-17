#pragma once
#include "../global.h"
#include <vector>
class Sprite {
      public:
	std::vector<unsigned char> sprite_buffer;

	Sprite(unsigned int width, unsigned int height);
	~Sprite();

	unsigned int width;
	unsigned int height;

	unsigned char* render(unsigned int sprite_Xy, unsigned int sprite_y);

	template <class Archive> void serialize(Archive& archive) { archive(sprite_buffer, width, height); }
};
