#include <SDL3/SDL.h>
#include <cereal/archives/binary.hpp>
#include <engine/game.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main(int argc, char* argv[]) {
	SDL_FRect rect;

	Game game("test");

	Pallete pallete;
	pallete.load_pallete_from_hex(aap_64);

	game.color_pallets["default"] = pallete;
	game.current_pallete	      = "default";

	Sprite sprite(1, 1);

	int w, h, comp;
	unsigned char* image = stbi_load("testimg.png", &w, &h, &comp, 0);

	if (comp == 4) {
		sprite.load_sprite_from_image(game.color_pallets[game.current_pallete], image, true);
		printf("4 channel\n");
	} else {
		sprite.load_sprite_from_image(game.color_pallets[game.current_pallete], image, false);
		printf("3 channel\n");
	}

	float sprite_y = 20;
	float sprite_x = 20;

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_GAMEPAD)) {
		printf("Error: SDL_Init(): %s\n", SDL_GetError());
		return -1;
	}

	SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE);

	SDL_Window* window     = SDL_CreateWindow("test", 640, 480, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	SDL_SetRenderLogicalPresentation(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	SDL_Event e;
	bool quit = false;

	unsigned int previous_ticks = SDL_GetTicks();
	float delta_time	    = 0.0f;

	unsigned int start_time	 = SDL_GetTicks();
	unsigned int frame_count = 0;

	while (!quit) {

		unsigned int current_time = SDL_GetTicks();
		frame_count++;

		unsigned int current_ticks = SDL_GetTicks();
		delta_time     = (current_ticks - previous_ticks) / 1000.0f; // Convert milliseconds to seconds
		previous_ticks = current_ticks;

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		SDL_RenderClear(renderer);

		// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		const bool* keystate = SDL_GetKeyboardState(NULL);

		if (keystate[SDL_SCANCODE_LEFT]) {
			sprite_x -= 100 * delta_time;
		}

		if (keystate[SDL_SCANCODE_RIGHT]) {
			sprite_x += 100 * delta_time;
		}

		if (keystate[SDL_SCANCODE_UP]) {
			sprite_y -= 100 * delta_time;
		}

		if (keystate[SDL_SCANCODE_DOWN]) {
			sprite_y += 100 * delta_time;
		}

		for (unsigned int y = 0; y < sprite.height * 8; y++) {
			for (unsigned int x = 0; x < sprite.width * 8; x++) {
				if (sprite.sprite_buffer[y * sprite.width * 8 + x] == 0) {
					continue;
				} else {
					Color color = game.color_pallets[game.current_pallete]
							  .colors[sprite.sprite_buffer[y * sprite.width * 8 + x]];
					SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

					if (color.a == 0) {
						continue;
					}
				}

				rect = {(float)x * 2 + (sprite_x), (float)y * 2 + (sprite_y), 2, 2};
				SDL_RenderFillRect(renderer, &rect);
			}
		}

		if (current_time - start_time >= 1000) {
			float fps = frame_count * 1000.0f / (current_time - start_time);
			std::cout << "FPS: " << fps << std::endl;
			frame_count = 0;
			start_time  = current_time;
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
