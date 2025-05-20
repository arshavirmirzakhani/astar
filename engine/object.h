#pragma once
#include "graphics/sprite.h"
#include <map>
#include <string>
#include <vector>

class Object {
      public:
	Object(std::string type);
	~Object();

	Sprite render();

	float position_x;
	float position_y;

	std::string type_name;
	unsigned int current_frame;
	int frame_per_tick;
	std::string current_animation_state;
	std::map<std::string, std::vector<Sprite>> all_sprites;
};
