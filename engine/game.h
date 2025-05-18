#pragma once
#include "default_palletes.h"
#include "global.h"
#include "object.h"
#include "scene.h"
#include <SDL3/SDL.h>
#include <fstream>

class Game {

      public:
	Game(std::string name);
	~Game();

	std::string name;
	char engine_version[3] = {0};

	std::map<std::string, int> object_types;

	std::map<std::string, Scene> scenes;

	std::vector<unsigned char> screen_buffer;

	std::string current_pallete;
	std::map<std::string, Pallete> color_pallets;

	void process();
	void render();

	void add_object(Object object);

	template <class Archive> void serialize(Archive& archive) {
		archive(name, engine_version, object_types, current_pallete, color_pallets);
	}
};
