#pragma once
#include "keycodes.h"
#include <cereal/archives/binary.hpp>
#include <cereal/types/complex.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/vector.hpp>
#include <map>
#include <math.h>
#include <string>
#include <vector>

const int SCREEN_WIDTH	= 240;
const int SCREEN_HEIGHT = 160;

extern float CAMERA_POSITION_X;
extern float CAMERA_POSITION_Y;

struct Color {
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 255;

	template <class Archive> void serialize(Archive& archive) { archive(r, g, b, a); }
};

struct Pallete {
	Color colors[127];

	void load_pallete_from_hex(std::string input_data);

	template <class Archive> void serialize(Archive& archive) { archive(colors); }
};