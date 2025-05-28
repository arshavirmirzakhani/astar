#pragma once
#include "default_palletes.h"
#include "global.h"
#include "object.h"
#include "scene.h"
#include <fstream>

class Game {

      public:
	Game(std::string name);
	~Game();

	std::string name;
	char engine_version[3] = {0};

	std::map<std::string, ObjectType> object_types;

	Pallete pallete;

	std::string current_scene;
	std::string init_scene;

	std::map<std::string, Scene> scenes;
	std::map<std::string, Sprite> sprites;
	std::vector<unsigned char> screen_buffer;

	std::vector<KEY_CODE> pressed_keys;

	void init();
	void process(float delta, std::vector<KEY_CODE> input_codes);
	void render();

	void add_object(Object object);

	template <class Archive> void serialize(Archive& archive) { archive(name, engine_version, object_types, scenes, init_scene, pallete, sprites); }
};
