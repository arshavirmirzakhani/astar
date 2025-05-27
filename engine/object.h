#pragma once
#include "global.h"
#include "graphics/sprite.h"
#include <map>
#include <sol/sol.hpp>
#include <string>
#include <vector>

class ObjectType {
      private:
	/* data */
      public:
	ObjectType();
	~ObjectType();

	std::string script;

	std::string default_animation_state;

	std::map<std::string, std::vector<std::string>> all_animation_states;
	int frame_per_tick;

	template <class Archive> void serialize(Archive& archive) {
		archive(script, all_animation_states, default_animation_state, frame_per_tick);
	}
};

class Object {
      public:
	Object();
	Object(std::string type);
	~Object();

	void expose_keycodes_as_constants(const std::unordered_map<std::string, KEY_CODE>& map);

	float position_x;
	float position_y;

	std::string name;

	std::string type_name;
	ObjectType type;

	unsigned int current_frame;
	int frame_per_tick;
	std::string current_animation_state;

	Sprite* current_sprite;

	std::shared_ptr<sol::state> lua_engine;

	void process(float delta, std::vector<KEY_CODE> input_codes);

	template <class Archive> void serialize(Archive& archive) {
		archive(name, position_x, position_y, type_name, current_frame, frame_per_tick,
			current_animation_state);
	}
};
