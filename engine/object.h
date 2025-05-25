#pragma once
#include "graphics/sprite.h"
#include "script_engine/script_engine.h"
#include <map>
#include <string>
#include <vector>

class ObjectType {
      private:
	/* data */
      public:
	ObjectType();
	~ObjectType();

	std::string script;

	std::map<std::string, std::vector<std::string>> all_animation_states;

	template <class Archive> void serialize(Archive& archive) { archive(script, all_animation_states); }
};

class Object {
      public:
	Object();
	Object(std::string type);
	~Object();

	float position_x;
	float position_y;

	std::string name;
	std::string type_name;

	std::string script;

	ScriptEngine* script_engine;

	unsigned int current_frame;
	int frame_per_tick;
	std::string current_animation_state;

	Sprite* current_sprite;

	template <class Archive> void serialize(Archive& archive) {
		archive(name, type_name, current_frame, frame_per_tick, current_animation_state);
	}
};
