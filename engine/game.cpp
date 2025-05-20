#include "game.h"

Game::Game(std::string name) {
	this->screen_buffer	 = std::vector<unsigned char>(SCREEN_WIDTH * SCREEN_HEIGHT, 0);
	this->sprites["default"] = Sprite(1, 1);
}

Game::~Game() {}

void Game::render() {
	this->screen_buffer = std::vector<unsigned char>(SCREEN_WIDTH * SCREEN_HEIGHT, 0);

	Object& current_object = this->scenes["test"].objects[0];
	Sprite sprite	       = current_object.render();

	int sprite_x_start = (int)roundf(current_object.position_x);
	int sprite_y_start = (int)roundf(current_object.position_y);

	int sprite_pixel_width	= sprite.width * 8;
	int sprite_pixel_height = sprite.height * 8;

	int sprite_x_end = sprite_x_start + sprite_pixel_width;
	int sprite_y_end = sprite_y_start + sprite_pixel_height;

	for (int y = std::max(0, sprite_y_start); y < std::min((int)SCREEN_HEIGHT, sprite_y_end); y++) {
		for (int x = std::max(0, sprite_x_start); x < std::min((int)SCREEN_WIDTH, sprite_x_end); x++) {
			int sprite_x = x - sprite_x_start;
			int sprite_y = y - sprite_y_start;

			int sprite_index = sprite_y * sprite_pixel_width + sprite_x;

			if (sprite_index < 0 || sprite_index >= sprite.sprite_buffer.size())
				continue;

			unsigned char pixel = sprite.sprite_buffer[sprite_index];

			if (pixel != 0) {
				screen_buffer[y * SCREEN_WIDTH + x] = pixel;
			}
		}
	}
}
