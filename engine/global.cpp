#include "global.h"
#include <cstring>

float CAMERA_POSITION_X = 0;
float CAMERA_POSITION_Y = 0;

unsigned char hex_component_to_uchar(const std::string& hex) { return static_cast<unsigned char>(std::stoi(hex, nullptr, 16)); }

Color hex_to_rgba(const std::string& hex) {
	std::string clean_hex = hex;
	if (hex[0] == '#')
		clean_hex = hex.substr(1);

	if (clean_hex.size() != 6 && clean_hex.size() != 8) {
		throw std::invalid_argument("Hex color must be 6 or 8 characters long");
	}

	Color color;
	color.r = hex_component_to_uchar(clean_hex.substr(0, 2));
	color.g = hex_component_to_uchar(clean_hex.substr(2, 2));
	color.b = hex_component_to_uchar(clean_hex.substr(4, 2));
	color.a = (clean_hex.size() == 8) ? hex_component_to_uchar(clean_hex.substr(6, 2)) : 255;

	return color;
}

void Pallete::load_pallete_from_hex(std::string input_data) {
	std::stringstream data(input_data);
	std::string segment;
	std::vector<std::string> hexlist;

	for (int i = 0; i < 128; ++i) {
		this->colors[i].r = 0;
		this->colors[i].g = 0;
		this->colors[i].b = 0;
		this->colors[i].a = 0;
	}

	while (std::getline(data, segment, ' ')) {
		hexlist.push_back(segment);
	}

	for (unsigned i = 0; i < 127 && i < hexlist.size(); i++) {
		this->colors[i] = hex_to_rgba(hexlist[i]);
	}
}
