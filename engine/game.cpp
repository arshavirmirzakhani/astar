#include "game.h"

Game::Game(std::string name) {
	this->screen_buffer	 = std::vector<unsigned char>(SCREEN_WIDTH * SCREEN_HEIGHT, 0);
	this->sprites["default"] = Sprite(1, 1);
}

Game::~Game() {}

void Game::render() {
	this->screen_buffer = std::vector<unsigned char>(SCREEN_WIDTH * SCREEN_HEIGHT, 0);

	Object current_object = this->scenes["test"].objects[0];
	Sprite sprite	      = current_object.render();

	int sprite_x_start = scenes["test"].objects[0].position_x;
	int sprite_y_start = scenes["test"].objects[0].position_y;

	int sprite_x_end = sprite_x_start + (sprite.width * 8);
	int sprite_y_end = sprite_y_start + (sprite.height * 8);

	int sprite_pixel_width	= sprite.width * 8;  // total pixel width of sprite
	int sprite_pixel_height = sprite.height * 8; // total pixel height of sprite

	for (unsigned int y = 0; y < SCREEN_HEIGHT; y++) {
		for (unsigned int x = 0; x < SCREEN_WIDTH; x++) {
			if (x >= sprite_x_start && x < sprite_x_end && y >= sprite_y_start && y < sprite_y_end) {

				int sprite_x = x - sprite_x_start;
				int sprite_y = y - sprite_y_start;

				if (sprite.sprite_buffer[sprite_y * sprite_pixel_width + sprite_x] == 0) {
					screen_buffer[y * SCREEN_WIDTH + x] = 0;
					continue;
				}
				screen_buffer[y * SCREEN_WIDTH + x] =
				    sprite.sprite_buffer[sprite_y * sprite_pixel_width + sprite_x];
			}
		}
	}
}
