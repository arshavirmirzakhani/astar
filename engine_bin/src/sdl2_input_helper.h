#pragma once
#include <SDL.h>
#include <cereal/archives/binary.hpp>
#include <engine/game.h>

KEY_CODE SDL2_scancode_to_enum(SDL_Scancode scancode);

KEY_CODE SDL2_mouse_to_enum(Uint8 button);

KEY_CODE SDL2_gamepad_to_enum(SDL_GameControllerButton button);

std::vector<KEY_CODE> get_pressed_keys_keyboard(const Uint8* keystate);

std::vector<KEY_CODE> get_pressed_keys_mouse(Uint32 mouse_state);

std::vector<KEY_CODE> get_pressed_keys_gamepad(SDL_GameController gamepad);

std::vector<KEY_CODE> get_pressed_keys(const Uint8* keyboard_state, Uint32 mouse_state, SDL_GameController* gamepad);
