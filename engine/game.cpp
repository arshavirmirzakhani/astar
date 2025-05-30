#include "game.h"

Game::Game(std::string name) {
	this->name = name;

	this->screen_buffer		       = std::vector<unsigned char>(SCREEN_WIDTH * SCREEN_HEIGHT, 0);
	this->sprites["default"]	       = Sprite(1, 1);
	this->sprites["default"].sprite_buffer = std::vector<unsigned char>(8 * 8, 0);
	;
}

Game::Game() {
	this->screen_buffer		       = std::vector<unsigned char>(SCREEN_WIDTH * SCREEN_HEIGHT, 0);
	this->sprites["default"]	       = Sprite(1, 1);
	this->sprites["default"].sprite_buffer = std::vector<unsigned char>(8 * 8, 0);
	;
}

Game::~Game() {}

void Game::init() {
	for (auto& [name, scene] : this->scenes) {
		for (auto& object : scene.objects) {
			object.second.type = this->object_types[object.second.type_name];
			object.second.current_sprite =
			    &this->sprites[object.second.type.all_animation_states[object.second.current_animation_state][object.second.current_frame].first];
		}
	}

	current_scene = init_scene;
}

void Game::process(float delta, std::vector<KEY_CODE> input_codes) {
	for (auto& object : this->scenes[current_scene].objects) {
		object.second.process(delta, input_codes);
		object.second.current_sprite =
		    &this->sprites[object.second.type.all_animation_states[object.second.current_animation_state][object.second.current_frame].first];
	}
}

void Game::render() {
	this->screen_buffer = std::vector<unsigned char>(SCREEN_WIDTH * SCREEN_HEIGHT, 0);

	for (auto& current_object : this->scenes[this->current_scene].objects) {
		Sprite sprite = *current_object.second.current_sprite;

		int sprite_x_start = (int)roundf(current_object.second.position_x) - (int)CAMERA_POSITION_X;
		int sprite_y_start = (int)roundf(current_object.second.position_y) - (int)CAMERA_POSITION_Y;

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
}
