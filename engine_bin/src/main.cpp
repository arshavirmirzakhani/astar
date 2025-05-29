#ifdef __EMSCRIPTEN__
#include <SDL.h>
#include <SDL_gamepad.h>
#else
#include <SDL3/SDL.h>
#include <SDL3/SDL_gamepad.h>
#endif

#include <cereal/archives/json.hpp>
#include <engine/game.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "sdl3_input_helper.h"
#include <stb_image.h>

float MOUSE_POS_X = 0;
float MOUSE_POS_Y = 0;

int main(int argc, char* argv[]) {
	SDL_FRect rect;

	std::fstream fs("res.astar", std::ios::in);

	if (!fs) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open game data!");
		return -1;
	}

	cereal::JSONInputArchive archive(fs);

	Game game;

	SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "before input");
	archive(game);
	SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "after input");

	fs.flush();
	fs.close();

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_AUDIO)) {
		printf("Error: SDL_Init(): %s\n", SDL_GetError());
		return -1;
	}

	SDL_Gamepad* gamepad_state = NULL;

	SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE);

	SDL_Window* window     = SDL_CreateWindow(game.name.c_str(), 640, 480, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
	SDL_SetRenderLogicalPresentation(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	SDL_Event e;
	bool quit = false;

	Uint64 now  = SDL_GetPerformanceCounter();
	Uint64 last = 0;
	float delta = 0.0;

	while (!quit) {
		uint64_t current_time = SDL_GetTicks();

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		SDL_RenderClear(renderer);

		// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		const bool* keyboard_state = SDL_GetKeyboardState(NULL);
		Uint32 mouse_state	   = SDL_GetMouseState(&MOUSE_POS_X, &MOUSE_POS_Y);

		const bool* keystate = SDL_GetKeyboardState(NULL);

		game.process(delta, get_pressed_keys(keyboard_state, mouse_state, gamepad_state));

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

				rect = {(float)x, (float)y, 1, 1};
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
