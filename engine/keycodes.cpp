#include "keycodes.h"

std::unordered_map<std::string, KEY_CODE> keycode_map = {{"KEY_NONE", KEY_NONE},

							 // Alphabet
							 {"KEY_A", KEY_A},
							 {"KEY_B", KEY_B},
							 {"KEY_C", KEY_C},
							 {"KEY_D", KEY_D},
							 {"KEY_E", KEY_E},
							 {"KEY_F", KEY_F},
							 {"KEY_G", KEY_G},
							 {"KEY_H", KEY_H},
							 {"KEY_I", KEY_I},
							 {"KEY_J", KEY_J},
							 {"KEY_K", KEY_K},
							 {"KEY_L", KEY_L},
							 {"KEY_M", KEY_M},
							 {"KEY_N", KEY_N},
							 {"KEY_O", KEY_O},
							 {"KEY_P", KEY_P},
							 {"KEY_Q", KEY_Q},
							 {"KEY_R", KEY_R},
							 {"KEY_S", KEY_S},
							 {"KEY_T", KEY_T},
							 {"KEY_U", KEY_U},
							 {"KEY_V", KEY_V},
							 {"KEY_W", KEY_W},
							 {"KEY_X", KEY_X},
							 {"KEY_Y", KEY_Y},
							 {"KEY_Z", KEY_Z},

							 // Numbers
							 {"KEY_0", KEY_0},
							 {"KEY_1", KEY_1},
							 {"KEY_2", KEY_2},
							 {"KEY_3", KEY_3},
							 {"KEY_4", KEY_4},
							 {"KEY_5", KEY_5},
							 {"KEY_6", KEY_6},
							 {"KEY_7", KEY_7},
							 {"KEY_8", KEY_8},
							 {"KEY_9", KEY_9},

							 // Function keys
							 {"KEY_F1", KEY_F1},
							 {"KEY_F2", KEY_F2},
							 {"KEY_F3", KEY_F3},
							 {"KEY_F4", KEY_F4},
							 {"KEY_F5", KEY_F5},
							 {"KEY_F6", KEY_F6},
							 {"KEY_F7", KEY_F7},
							 {"KEY_F8", KEY_F8},
							 {"KEY_F9", KEY_F9},
							 {"KEY_F10", KEY_F10},
							 {"KEY_F11", KEY_F11},
							 {"KEY_F12", KEY_F12},

							 // Navigation keys
							 {"KEY_UP", KEY_UP},
							 {"KEY_DOWN", KEY_DOWN},
							 {"KEY_LEFT", KEY_LEFT},
							 {"KEY_RIGHT", KEY_RIGHT},
							 {"KEY_HOME", KEY_HOME},
							 {"KEY_END", KEY_END},
							 {"KEY_PAGE_UP", KEY_PAGE_UP},
							 {"KEY_PAGE_DOWN", KEY_PAGE_DOWN},
							 {"KEY_INSERT", KEY_INSERT},
							 {"KEY_DELETE", KEY_DELETE},

							 // Control keys
							 {"KEY_ENTER", KEY_ENTER},
							 {"KEY_ESCAPE", KEY_ESCAPE},
							 {"KEY_BACKSPACE", KEY_BACKSPACE},
							 {"KEY_TAB", KEY_TAB},
							 {"KEY_SPACE", KEY_SPACE},
							 {"KEY_SHIFT", KEY_SHIFT},
							 {"KEY_CTRL", KEY_CTRL},
							 {"KEY_ALT", KEY_ALT},
							 {"KEY_CAPS_LOCK", KEY_CAPS_LOCK},

							 // Punctuation
							 {"KEY_MINUS", KEY_MINUS},
							 {"KEY_EQUALS", KEY_EQUALS},
							 {"KEY_LEFT_BRACKET", KEY_LEFT_BRACKET},
							 {"KEY_RIGHT_BRACKET", KEY_RIGHT_BRACKET},
							 {"KEY_BACKSLASH", KEY_BACKSLASH},
							 {"KEY_SEMICOLON", KEY_SEMICOLON},
							 {"KEY_APOSTROPHE", KEY_APOSTROPHE},
							 {"KEY_GRAVE", KEY_GRAVE},
							 {"KEY_COMMA", KEY_COMMA},
							 {"KEY_PERIOD", KEY_PERIOD},
							 {"KEY_SLASH", KEY_SLASH},

							 // Mouse buttons (shortened)
							 {"KEY_MOUSE_L", KEY_MOUSE_LEFT},
							 {"KEY_MOUSE_M", KEY_MOUSE_MIDDLE},
							 {"KEY_MOUSE_R", KEY_MOUSE_RIGHT},

							 // Controller buttons (shortened)
							 {"KEY_CONTROLLER_BTN_SOUTH", KEY_CONTROLLER_BUTTON_SOUTH},
							 {"KEY_CONTROLLER_BTN_EAST", KEY_CONTROLLER_BUTTON_EAST},
							 {"KEY_CONTROLLER_BTN_WEST", KEY_CONTROLLER_BUTTON_WEST},
							 {"KEY_CONTROLLER_BTN_NORTH", KEY_CONTROLLER_BUTTON_NORTH},
							 {"KEY_CONTROLLER_BACK", KEY_CONTROLLER_BACK},
							 {"KEY_CONTROLLER_GUIDE", KEY_CONTROLLER_GUIDE},
							 {"KEY_CONTROLLER_START", KEY_CONTROLLER_START},
							 {"KEY_CONTROLLER_L_STICK", KEY_CONTROLLER_LEFT_STICK},
							 {"KEY_CONTROLLER_R_STICK", KEY_CONTROLLER_RIGHT_STICK},
							 {"KEY_CONTROLLER_L_SHOULDER", KEY_CONTROLLER_LEFT_SHOULDER},
							 {"KEY_CONTROLLER_R_SHOULDER", KEY_CONTROLLER_RIGHT_SHOULDER},
							 {"KEY_CONTROLLER_DPAD_UP", KEY_CONTROLLER_DPAD_UP},
							 {"KEY_CONTROLLER_DPAD_DOWN", KEY_CONTROLLER_DPAD_DOWN},
							 {"KEY_CONTROLLER_DPAD_LEFT", KEY_CONTROLLER_DPAD_LEFT},
							 {"KEY_CONTROLLER_DPAD_RIGHT", KEY_CONTROLLER_DPAD_RIGHT},
							 {"KEY_CONTROLLER_MISC1", KEY_CONTROLLER_MISC1},
							 {"KEY_CONTROLLER_TOUCHPAD", KEY_CONTROLLER_TOUCHPAD}};

KEY_CODE string_to_key_code(const std::string& name) {
	auto it = keycode_map.find(name);
	if (it != keycode_map.end()) {
		return it->second;
	} else {
		return KEY_NONE; // or some other fallback
	}
}
