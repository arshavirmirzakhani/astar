#pragma once
#include "../global.h"
#include <vector>

class Sprite {
      public:
	std::vector<unsigned char> sprite_buffer;

	Sprite();
	Sprite(unsigned int width, unsigned int height);
	~Sprite();

	void load_sprite_from_image(Pallete pallete, unsigned char* data, bool is_rgba);

	unsigned int width;
	unsigned int height;

	template <class Archive> void serialize(Archive& archive) { archive(sprite_buffer, width, height); }
};
