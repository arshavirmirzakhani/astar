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

int find_closest_palette_index(const Pallete& palette, unsigned char r, unsigned char g, unsigned char b,
			       unsigned char a) {
	int bestIndex	 = 0;
	int bestDistance = INT_MAX;

	for (int i = 0; i < 128; ++i) {
		const Color& c = palette.colors[i];
		int dr	       = c.r - r;
		int dg	       = c.g - g;
		int db	       = c.b - b;
		int da	       = c.a - a;
		int distance   = dr * dr + dg * dg + db * db + da * da; // Euclidean distance squared

		if (distance < bestDistance) {
			bestDistance = distance;
			bestIndex    = i;
		}
	}

	return bestIndex;
}

void Sprite::load_sprite_from_image(const Pallete& palette, unsigned char* image_data, bool has_alpha) {
	int sprite_width  = width * 8;
	int sprite_height = height * 8;
	sprite_buffer.resize(sprite_width * sprite_height);

	int channels = has_alpha ? 4 : 3;

	this->original_image_data.assign(image_data, image_data + sprite_width * sprite_height * channels);
	this->original_has_alpha = has_alpha;

	for (int y = 0; y < sprite_height; ++y) {
		for (int x = 0; x < sprite_width; ++x) {
			int index	= (y * sprite_width + x) * channels;
			unsigned char r = image_data[index + 0];
			unsigned char g = image_data[index + 1];
			unsigned char b = image_data[index + 2];
			unsigned char a = has_alpha ? image_data[index + 3] : 255;

			int palette_index		    = find_closest_palette_index(palette, r, g, b, a);
			sprite_buffer[y * sprite_width + x] = palette_index;
		}
	}
}

void Sprite::regenerate_with_current_palette(const Pallete& palette, bool has_alpha) {
	if (&original_image_data != nullptr) {
		load_sprite_from_image(palette, original_image_data.data(), has_alpha);
	}
}