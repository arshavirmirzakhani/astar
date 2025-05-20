#include "object.h"

Object::Object(std::string type) {
	this->type_name	 = type;
	this->position_x = 0;
	this->position_y = 0;
}

Object::~Object() {}

Sprite Object::render() { return this->all_sprites[this->current_animation_state][this->current_frame]; }