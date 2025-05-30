#include "object.h"

ObjectType::ObjectType() {}
ObjectType::~ObjectType() {}

void Object::expose_keycodes_as_constants(const std::unordered_map<std::string, KEY_CODE>& map) {
	for (const auto& [name, key] : map) {
		this->lua_engine->set(name, key);
	}
}

Object::Object(std::string type) {
	lua_engine = std::make_shared<sol::state>();
	this->lua_engine->open_libraries(sol::lib::base, sol::lib::math);
	expose_keycodes_as_constants(keycode_map);

	this->type_name	 = type;
	this->position_x = 0;
	this->position_y = 0;
}

Object::Object() {
	lua_engine = std::make_shared<sol::state>();
	this->lua_engine->open_libraries(sol::lib::base, sol::lib::math);
	expose_keycodes_as_constants(keycode_map);

	this->type_name	 = "";
	this->position_x = 0;
	this->position_y = 0;
}

Object::~Object() {}

void Object::process(float delta, std::vector<KEY_CODE> input_codes) {

	this->lua_engine->set("DELTA", delta);
	this->lua_engine->set("POSITION_X", this->position_x);
	this->lua_engine->set("POSITION_Y", this->position_y);
	this->lua_engine->set("CAMERA_POSITION_X", CAMERA_POSITION_X);
	this->lua_engine->set("CAMERA_POSITION_Y", CAMERA_POSITION_Y);

	this->lua_engine->set_function("is_key_pressed", [input_codes](std::string key) -> bool {
		return (std::find(input_codes.begin(), input_codes.end(), keycode_map[key]) != input_codes.end()) ? true : false;
	});

	this->lua_engine->script("main()");

	this->position_x = this->lua_engine->get<float>("POSITION_X");
	this->position_y = this->lua_engine->get<float>("POSITION_Y");

	CAMERA_POSITION_X = this->lua_engine->get<float>("CAMERA_POSITION_X");
	CAMERA_POSITION_Y = this->lua_engine->get<float>("CAMERA_POSITION_Y");
}