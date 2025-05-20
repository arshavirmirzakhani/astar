#include "object.h"

Object::Object(std::string type) { this->type_name = type; }

Object::~Object() {}

Sprite Object::render() { return this->all_sprites[this->current_animation_state][this->current_frame]; }