#include "keycodes.h"

std::string key_code_to_string(KEY_CODE key) {
	switch (key) {
	case KEY_NONE:
		return "None";

	// Alphabet
	case KEY_A:
		return "A";
	case KEY_B:
		return "B";
	case KEY_C:
		return "C";
	case KEY_D:
		return "D";
	case KEY_E:
		return "E";
	case KEY_F:
		return "F";
	case KEY_G:
		return "G";
	case KEY_H:
		return "H";
	case KEY_I:
		return "I";
	case KEY_J:
		return "J";
	case KEY_K:
		return "K";
	case KEY_L:
		return "L";
	case KEY_M:
		return "M";
	case KEY_N:
		return "N";
	case KEY_O:
		return "O";
	case KEY_P:
		return "P";
	case KEY_Q:
		return "Q";
	case KEY_R:
		return "R";
	case KEY_S:
		return "S";
	case KEY_T:
		return "T";
	case KEY_U:
		return "U";
	case KEY_V:
		return "V";
	case KEY_W:
		return "W";
	case KEY_X:
		return "X";
	case KEY_Y:
		return "Y";
	case KEY_Z:
		return "Z";

	// Numbers
	case KEY_0:
		return "0";
	case KEY_1:
		return "1";
	case KEY_2:
		return "2";
	case KEY_3:
		return "3";
	case KEY_4:
		return "4";
	case KEY_5:
		return "5";
	case KEY_6:
		return "6";
	case KEY_7:
		return "7";
	case KEY_8:
		return "8";
	case KEY_9:
		return "9";

	// Function keys
	case KEY_F1:
		return "F1";
	case KEY_F2:
		return "F2";
	case KEY_F3:
		return "F3";
	case KEY_F4:
		return "F4";
	case KEY_F5:
		return "F5";
	case KEY_F6:
		return "F6";
	case KEY_F7:
		return "F7";
	case KEY_F8:
		return "F8";
	case KEY_F9:
		return "F9";
	case KEY_F10:
		return "F10";
	case KEY_F11:
		return "F11";
	case KEY_F12:
		return "F12";

	// Navigation keys
	case KEY_UP:
		return "Up";
	case KEY_DOWN:
		return "Down";
	case KEY_LEFT:
		return "Left";
	case KEY_RIGHT:
		return "Right";
	case KEY_HOME:
		return "Home";
	case KEY_END:
		return "End";
	case KEY_PAGE_UP:
		return "Page Up";
	case KEY_PAGE_DOWN:
		return "Page Down";
	case KEY_INSERT:
		return "Insert";
	case KEY_DELETE:
		return "Delete";

	// Control keys
	case KEY_ENTER:
		return "Enter";
	case KEY_ESCAPE:
		return "Escape";
	case KEY_BACKSPACE:
		return "Backspace";
	case KEY_TAB:
		return "Tab";
	case KEY_SPACE:
		return "Space";
	case KEY_SHIFT:
		return "Shift";
	case KEY_CTRL:
		return "Ctrl";
	case KEY_ALT:
		return "Alt";
	case KEY_CAPS_LOCK:
		return "Caps Lock";

	// Punctuation
	case KEY_MINUS:
		return "-";
	case KEY_EQUALS:
		return "=";
	case KEY_LEFT_BRACKET:
		return "[";
	case KEY_RIGHT_BRACKET:
		return "]";
	case KEY_BACKSLASH:
		return "\\";
	case KEY_SEMICOLON:
		return ";";
	case KEY_APOSTROPHE:
		return "'";
	case KEY_GRAVE:
		return "`";
	case KEY_COMMA:
		return ",";
	case KEY_PERIOD:
		return ".";
	case KEY_SLASH:
		return "/";

	// Mouse buttons
	case KEY_MOUSE_LEFT:
		return "Mouse Left";
	case KEY_MOUSE_MIDDLE:
		return "Mouse Middle";
	case KET_MOUSE_RIGHT:
		return "Mouse Right";

	// Controller keys
	case KEY_CONTROLLER_BUTTON_SOUTH:
		return "Controller South";
	case KEY_CONTROLLER_BUTTON_EAST:
		return "Controller East";
	case KEY_CONTROLLER_BUTTON_WEST:
		return "Controller West";
	case KEY_CONTROLLER_BUTTON_NORTH:
		return "Controller North";
	case KEY_CONTROLLER_BACK:
		return "Controller Back";
	case KEY_CONTROLLER_GUIDE:
		return "Controller Guide";
	case KEY_CONTROLLER_START:
		return "Controller Start";
	case KEY_CONTROLLER_LEFT_STICK:
		return "Controller Left Stick";
	case KEY_CONTROLLER_RIGHT_STICK:
		return "Controller Right Stick";
	case KEY_CONTROLLER_LEFT_SHOULDER:
		return "Controller Left Shoulder";
	case KEY_CONTROLLER_RIGHT_SHOULDER:
		return "Controller Right Shoulder";
	case KEY_CONTROLLER_DPAD_UP:
		return "D-Pad Up";
	case KEY_CONTROLLER_DPAD_DOWN:
		return "D-Pad Down";
	case KEY_CONTROLLER_DPAD_LEFT:
		return "D-Pad Left";
	case KEY_CONTROLLER_DPAD_RIGHT:
		return "D-Pad Right";
	case KEY_CONTROLLER_MISC1:
		return "Controller Misc1";
	case KEY_CONTROLLER_TOUCHPAD:
		return "Touchpad";

	default:
		return "Unknown";
	}
}
