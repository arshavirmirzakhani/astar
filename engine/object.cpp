#include "object.h"

ObjectType::ObjectType() {}
ObjectType::~ObjectType() {}

Object::Object(std::string type) {
	this->type_name	 = type;
	this->position_x = 0;
	this->position_y = 0;
}

Object::Object() {
	this->type_name	 = "";
	this->position_x = 0;
	this->position_y = 0;
}

Object::~Object() {}
