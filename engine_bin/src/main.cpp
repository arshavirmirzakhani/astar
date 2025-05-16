#include <SDL3/SDL.h>
#include <engine/game.h>
#include <iostream>

int main(int argc, char* argv[]) {

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_GAMEPAD)) {
		printf("Error: SDL_Init(): %s\n", SDL_GetError());
		return -1;
	}

	SDL_Window* window     = SDL_CreateWindow("test", 640, 480, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	SDL_SetRenderLogicalPresentation(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	SDL_Event e;
	bool quit = false;

	Game game("test");

	SDL_FRect rect;

	int sprite_y = 20;
	int sprite_x = 20;

	while (!quit) {

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			if (e.type == SDL_EVENT_KEY_DOWN) {
				/* the pressed key was Escape? */
				if (e.key.key == SDLK_LEFT) {
					sprite_y -= 1;
				}
				if (e.key.key == SDLK_RIGHT) {
					sprite_y += 1;
				}
				if (e.key.key == SDLK_UP) {
					sprite_x -= 1;
				}
				if (e.key.key == SDLK_DOWN) {
					sprite_x += 1;
				}
			}
		}

		game.screen_buffer.clear();

		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				if (x >= sprite_y && x <= sprite_y + 20 && y >= sprite_x && y <= sprite_x + 40) {
					game.screen_buffer.push_back(1);
				}

				else {
					game.screen_buffer.push_back(0);
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				if (game.screen_buffer[y * SCREEN_WIDTH + x] == 1) {
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				} else {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				}

				rect = {(float)x, (float)y, 1, 1};
				SDL_RenderFillRect(renderer, &rect);
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
