#include <SDL.h>
#include <SDL_gamecontroller.h>
#include <cereal/archives/json.hpp>
#include <engine/game.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "sdl2_input_helper.h"
#include <stb_image.h>

int MOUSE_POS_X = 0;
int MOUSE_POS_Y = 0;

int main(int argc, char* argv[]) {
	Game game;
	SDL_Rect rect;

	std::fstream fs("res.astar", std::ios::in);

	if (!fs) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open game data!");
		return -1;
	}

	try {
		cereal::JSONInputArchive archive(fs);

		archive(game);

		fs.flush();
		fs.close();
	} catch (const std::exception& _) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load game data!");
		return -1;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		printf("Error: SDL_Init(): %s\n", SDL_GetError());
		return -1;
	}

	SDL_GameController* game_controller = NULL;
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			game_controller = SDL_GameControllerOpen(i);
			if (game_controller) {
				printf("Opened controller %d\n", i);
				break;
			} else {
				printf("Could not open gamecontroller %d: %s\n", i, SDL_GetError());
			}
		}
	}

	SDL_Window* window =
	    SDL_CreateWindow(game.name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL, 0);

	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Event e;
	bool quit = false;

	Uint64 now  = SDL_GetPerformanceCounter();
	Uint64 last = 0;
	float delta = 0.0;

	while (!quit) {
		uint64_t current_time = SDL_GetTicks();

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		const Uint8* keyboard_state = SDL_GetKeyboardState(0);
		Uint32 mouse_state	    = SDL_GetMouseState(&MOUSE_POS_X, &MOUSE_POS_Y);

		game.process(delta, get_pressed_keys(keyboard_state, mouse_state, game_controller));

		game.render();

		for (unsigned int y = 0; y < SCREEN_HEIGHT; y++) {
			for (unsigned int x = 0; x < SCREEN_WIDTH; x++) {
				if (game.screen_buffer[y * SCREEN_WIDTH + x] == 0) {
					continue;
				} else {
					Color color = game.pallete.colors[game.screen_buffer[y * SCREEN_WIDTH + x]];

					if (color.a == 0) {
						continue;
					}

					SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
				}

				rect = {(int)x, (int)y, 1, 1};
				SDL_RenderFillRect(renderer, &rect);
			}
		}

		last  = now;
		now   = SDL_GetPerformanceCounter();
		delta = static_cast<float>(now - last) / SDL_GetPerformanceFrequency();

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
