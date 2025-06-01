#pragma once
#include "../global.h"
#include <vector>

struct SpriteInfo {
	unsigned int begin_x = 0;
	unsigned int begin_y = 0;
	unsigned int width   = 1;
	unsigned int height  = 1;
	template <class Archive> void serialize(Archive& archive) { archive(begin_x, begin_y, width, height); }
};

class Sprite {
      public:
	std::vector<unsigned char> sprite_buffer;

	Sprite();
	Sprite(unsigned int width, unsigned int height);
	~Sprite();

	void load_sprite_from_image(const Pallete& palette, unsigned char* image_data, bool has_alpha);

	void regenerate_with_current_palette(const Pallete& palette, bool has_alpha);

	unsigned int width;
	unsigned int height;

	std::vector<unsigned char> original_image_data;
	bool original_has_alpha = false;

	template <class Archive> void serialize(Archive& archive) { archive(sprite_buffer, width, height, original_image_data, original_has_alpha); }
};
