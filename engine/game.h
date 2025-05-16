#pragma once
#include "global.h"
#include "object.h"
#include "scene.h"
#include <SDL3/SDL.h>
#include <fstream>

struct Color {
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 255;

	template <class Archive> void serialize(Archive& archive) { archive(r, g, b, a); }
};

struct Pallete {
	Color colors[127];

	template <class Archive> void serialize(Archive& archive) { archive(colors); }
};

class Game {

      public:
	Game(std::string name);
	~Game();

	std::string name;
	char engine_version[3] = {0};

	std::map<std::string, int> object_types;

	std::map<std::string, Scene> scenes;

	std::vector<unsigned char> screen_buffer;

	unsigned int current_pallete = 0;
	std::map<std::string, Pallete> color_pallets;

	void process();
	void render();

	void add_object(Object object);

	template <class Archive> void serialize(Archive& archive) {
		archive(name, engine_version, object_types, current_pallete, color_pallets);
	}
};
