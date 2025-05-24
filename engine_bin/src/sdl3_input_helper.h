#pragma once
#ifdef __EMSCRIPTEN__
#include <SDL.h>
#else
#include <SDL3/SDL.h>
#endif

#include <cereal/archives/binary.hpp>
#include <engine/game.h>

KEY_CODE SDL3_scancode_to_enum(SDL_Scancode scancode);

KEY_CODE SDL3_mouse_to_enum(Uint8 button);

KEY_CODE SDL3_gamepad_to_enum(SDL_GamepadButton button);

std::vector<KEY_CODE> get_pressed_keys_keyboard(const bool* keystate);

std::vector<KEY_CODE> get_pressed_keys_mouse(Uint32 mouse_state);

std::vector<KEY_CODE> get_pressed_keys_gamepad(SDL_Gamepad* gamepad);

std::vector<KEY_CODE> get_pressed_keys(const bool* keyboard_state, Uint32 mouse_state, SDL_Gamepad* gamepad);
