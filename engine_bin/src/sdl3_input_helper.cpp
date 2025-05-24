#include "sdl3_input_helper.h"

KEY_CODE SDL3_scancode_to_enum(SDL_Scancode scancode) {
	switch (scancode) {
	// Alphanumeric
	case SDL_SCANCODE_A:
		return KEY_A;
	case SDL_SCANCODE_B:
		return KEY_B;
	case SDL_SCANCODE_C:
		return KEY_C;
	case SDL_SCANCODE_D:
		return KEY_D;
	case SDL_SCANCODE_E:
		return KEY_E;
	case SDL_SCANCODE_F:
		return KEY_F;
	case SDL_SCANCODE_G:
		return KEY_G;
	case SDL_SCANCODE_H:
		return KEY_H;
	case SDL_SCANCODE_I:
		return KEY_I;
	case SDL_SCANCODE_J:
		return KEY_J;
	case SDL_SCANCODE_K:
		return KEY_K;
	case SDL_SCANCODE_L:
		return KEY_L;
	case SDL_SCANCODE_M:
		return KEY_M;
	case SDL_SCANCODE_N:
		return KEY_N;
	case SDL_SCANCODE_O:
		return KEY_O;
	case SDL_SCANCODE_P:
		return KEY_P;
	case SDL_SCANCODE_Q:
		return KEY_Q;
	case SDL_SCANCODE_R:
		return KEY_R;
	case SDL_SCANCODE_S:
		return KEY_S;
	case SDL_SCANCODE_T:
		return KEY_T;
	case SDL_SCANCODE_U:
		return KEY_U;
	case SDL_SCANCODE_V:
		return KEY_V;
	case SDL_SCANCODE_W:
		return KEY_W;
	case SDL_SCANCODE_X:
		return KEY_X;
	case SDL_SCANCODE_Y:
		return KEY_Y;
	case SDL_SCANCODE_Z:
		return KEY_Z;

	case SDL_SCANCODE_0:
		return KEY_0;
	case SDL_SCANCODE_1:
		return KEY_1;
	case SDL_SCANCODE_2:
		return KEY_2;
	case SDL_SCANCODE_3:
		return KEY_3;
	case SDL_SCANCODE_4:
		return KEY_4;
	case SDL_SCANCODE_5:
		return KEY_5;
	case SDL_SCANCODE_6:
		return KEY_6;
	case SDL_SCANCODE_7:
		return KEY_7;
	case SDL_SCANCODE_8:
		return KEY_8;
	case SDL_SCANCODE_9:
		return KEY_9;

	// Function keys
	case SDL_SCANCODE_F1:
		return KEY_F1;
	case SDL_SCANCODE_F2:
		return KEY_F2;
	case SDL_SCANCODE_F3:
		return KEY_F3;
	case SDL_SCANCODE_F4:
		return KEY_F4;
	case SDL_SCANCODE_F5:
		return KEY_F5;
	case SDL_SCANCODE_F6:
		return KEY_F6;
	case SDL_SCANCODE_F7:
		return KEY_F7;
	case SDL_SCANCODE_F8:
		return KEY_F8;
	case SDL_SCANCODE_F9:
		return KEY_F9;
	case SDL_SCANCODE_F10:
		return KEY_F10;
	case SDL_SCANCODE_F11:
		return KEY_F11;
	case SDL_SCANCODE_F12:
		return KEY_F12;

	// Navigation
	case SDL_SCANCODE_UP:
		return KEY_UP;
	case SDL_SCANCODE_DOWN:
		return KEY_DOWN;
	case SDL_SCANCODE_LEFT:
		return KEY_LEFT;
	case SDL_SCANCODE_RIGHT:
		return KEY_RIGHT;
	case SDL_SCANCODE_HOME:
		return KEY_HOME;
	case SDL_SCANCODE_END:
		return KEY_END;
	case SDL_SCANCODE_PAGEUP:
		return KEY_PAGE_UP;
	case SDL_SCANCODE_PAGEDOWN:
		return KEY_PAGE_DOWN;
	case SDL_SCANCODE_INSERT:
		return KEY_INSERT;
	case SDL_SCANCODE_DELETE:
		return KEY_DELETE;

	// Control
	case SDL_SCANCODE_RETURN:
		return KEY_ENTER;
	case SDL_SCANCODE_ESCAPE:
		return KEY_ESCAPE;
	case SDL_SCANCODE_BACKSPACE:
		return KEY_BACKSPACE;
	case SDL_SCANCODE_TAB:
		return KEY_TAB;
	case SDL_SCANCODE_SPACE:
		return KEY_SPACE;
	case SDL_SCANCODE_LSHIFT:
	case SDL_SCANCODE_RSHIFT:
		return KEY_SHIFT;
	case SDL_SCANCODE_LCTRL:
	case SDL_SCANCODE_RCTRL:
		return KEY_CTRL;
	case SDL_SCANCODE_LALT:
	case SDL_SCANCODE_RALT:
		return KEY_ALT;
	case SDL_SCANCODE_CAPSLOCK:
		return KEY_CAPS_LOCK;

	// Punctuation
	case SDL_SCANCODE_MINUS:
		return KEY_MINUS;
	case SDL_SCANCODE_EQUALS:
		return KEY_EQUALS;
	case SDL_SCANCODE_LEFTBRACKET:
		return KEY_LEFT_BRACKET;
	case SDL_SCANCODE_RIGHTBRACKET:
		return KEY_RIGHT_BRACKET;
	case SDL_SCANCODE_BACKSLASH:
		return KEY_BACKSLASH;
	case SDL_SCANCODE_SEMICOLON:
		return KEY_SEMICOLON;
	case SDL_SCANCODE_APOSTROPHE:
		return KEY_APOSTROPHE;
	case SDL_SCANCODE_GRAVE:
		return KEY_GRAVE;
	case SDL_SCANCODE_COMMA:
		return KEY_COMMA;
	case SDL_SCANCODE_PERIOD:
		return KEY_PERIOD;
	case SDL_SCANCODE_SLASH:
		return KEY_SLASH;

	default:
		return KEY_NONE;
	}
}

KEY_CODE SDL3_mouse_to_enum(Uint8 button) {
	switch (button) {
	case SDL_BUTTON_LEFT:
		return KEY_MOUSE_LEFT;
	case SDL_BUTTON_MIDDLE:
		return KEY_MOUSE_MIDDLE;
	case SDL_BUTTON_RIGHT:
		return KET_MOUSE_RIGHT;
	default:
		return KEY_NONE;
	}
}

KEY_CODE SDL3_gamepad_to_enum(SDL_GamepadButton button) {
	switch (button) {
	case SDL_GAMEPAD_BUTTON_SOUTH:
		return KEY_CONTROLLER_BUTTON_SOUTH;
	case SDL_GAMEPAD_BUTTON_EAST:
		return KEY_CONTROLLER_BUTTON_EAST;
	case SDL_GAMEPAD_BUTTON_WEST:
		return KEY_CONTROLLER_BUTTON_WEST;
	case SDL_GAMEPAD_BUTTON_NORTH:
		return KEY_CONTROLLER_BUTTON_NORTH;
	case SDL_GAMEPAD_BUTTON_BACK:
		return KEY_CONTROLLER_BACK;
	case SDL_GAMEPAD_BUTTON_GUIDE:
		return KEY_CONTROLLER_GUIDE;
	case SDL_GAMEPAD_BUTTON_START:
		return KEY_CONTROLLER_START;
	case SDL_GAMEPAD_BUTTON_LEFT_STICK:
		return KEY_CONTROLLER_LEFT_STICK;
	case SDL_GAMEPAD_BUTTON_RIGHT_STICK:
		return KEY_CONTROLLER_RIGHT_STICK;
	case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
		return KEY_CONTROLLER_LEFT_SHOULDER;
	case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
		return KEY_CONTROLLER_RIGHT_SHOULDER;
	case SDL_GAMEPAD_BUTTON_DPAD_UP:
		return KEY_CONTROLLER_DPAD_UP;
	case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
		return KEY_CONTROLLER_DPAD_DOWN;
	case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
		return KEY_CONTROLLER_DPAD_LEFT;
	case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
		return KEY_CONTROLLER_DPAD_RIGHT;
	case SDL_GAMEPAD_BUTTON_MISC1:
		return KEY_CONTROLLER_MISC1;
	case SDL_GAMEPAD_BUTTON_TOUCHPAD:
		return KEY_CONTROLLER_TOUCHPAD;
	default:
		return KEY_NONE;
	}
}

std::vector<KEY_CODE> get_pressed_keys_keyboard(const bool* keystate) {
	std::vector<KEY_CODE> pressed_keys;

	int numkeys;
	SDL_GetKeyboardState(&numkeys);

	for (int sc = 0; sc < numkeys; ++sc) {
		if (keystate[sc]) {
			KEY_CODE key = SDL3_scancode_to_enum(static_cast<SDL_Scancode>(sc));
			if (key != KEY_NONE)
				pressed_keys.push_back(key);
		}
	}

	return pressed_keys;
}

std::vector<KEY_CODE> get_pressed_keys_mouse(Uint32 mouse_state) {
	std::vector<KEY_CODE> pressed_buttons;

	for (Uint8 btn = SDL_BUTTON_LEFT; btn <= SDL_BUTTON_X2; ++btn) {
		if (mouse_state) {
			KEY_CODE key = SDL3_mouse_to_enum(btn);
			if (key != KEY_NONE)
				pressed_buttons.push_back(key);
		}
	}
	return pressed_buttons;
}

std::vector<KEY_CODE> get_pressed_keys_gamepad(SDL_Gamepad* gamepad) {
	std::vector<KEY_CODE> pressed_buttons;
	if (!gamepad)
		return pressed_buttons;

	for (int b = SDL_GAMEPAD_BUTTON_SOUTH; b <= SDL_GAMEPAD_BUTTON_TOUCHPAD; ++b) {
		if (SDL_GetGamepadButton(gamepad, static_cast<SDL_GamepadButton>(b))) {
			KEY_CODE key = SDL3_gamepad_to_enum(static_cast<SDL_GamepadButton>(b));
			if (key != KEY_NONE)
				pressed_buttons.push_back(key);
		}
	}
	return pressed_buttons;
}

std::vector<KEY_CODE> get_pressed_keys(const bool* keyboard_state, Uint32 mouse_state, SDL_Gamepad* gamepad) {
	std::vector<KEY_CODE> result;

	auto keyboard = get_pressed_keys_keyboard(keyboard_state);
	result.insert(result.end(), keyboard.begin(), keyboard.end());

	auto mouse = get_pressed_keys_mouse(mouse_state);
	result.insert(result.end(), mouse.begin(), mouse.end());

	auto gamepad_buttons = get_pressed_keys_gamepad(gamepad);
	result.insert(result.end(), gamepad_buttons.begin(), gamepad_buttons.end());

	return result;
}
