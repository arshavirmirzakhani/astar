#include "object.h"

Object::Object(std::string type) {
	this->type_name	 = type;
	this->position_x = 0;
	this->position_y = 0;
}

Object::Object() {
	this->type_name	 = "new object";
	this->position_x = 0;
	this->position_y = 0;
}

Object::~Object() {}

std::string Object::get_sprite_name() { return this->all_sprites[this->current_animation_state][this->current_frame]; }