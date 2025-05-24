#ifdef __EMSCRIPTEN__
#include <SDL.h>
#include <SDL_gamepad.h>
#else
#include <SDL3/SDL.h>
#include <SDL3/SDL_gamepad.h>
#endif

#include <cereal/archives/binary.hpp>
#include <engine/game.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "sdl3_input_helper.h"
#include <stb_image.h>

float MOUSE_POS_X = 0;
float MOUSE_POS_Y = 0;

int main(int argc, char* argv[]) {
	SDL_FRect rect;

	Game game("test");

	game.pallete.load_pallete_from_hex(aap_64);

	Object object("type");
	Sprite sprite(1, 1);

	int w, h, comp;
	unsigned char* image = stbi_load("assets/testimg.png", &w, &h, &comp, 0);

	if (comp == 4) {
		sprite.load_sprite_from_image(game.pallete, image, true);
		printf("4 channel\n");
	} else {
		sprite.load_sprite_from_image(game.pallete, image, false);
		printf("3 channel\n");
	}

	object.current_animation_state = "first";
	object.all_sprites["first"].push_back("test");
	object.current_frame = 0;

	game.sprites["test"] = sprite;

	Scene scene;
	scene.objects.push_back(object);
	game.scenes["test"] = std::move(scene);

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_AUDIO)) {
		printf("Error: SDL_Init(): %s\n", SDL_GetError());
		return -1;
	}

	SDL_Gamepad* gamepad_state = NULL;

	SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE);

	SDL_Window* window     = SDL_CreateWindow("test", 640, 480, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
	SDL_SetRenderLogicalPresentation(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	SDL_Event e;
	bool quit = false;

	uint64_t previous_ticks = SDL_GetTicks();
	float delta_time	= 0.0f;

	uint64_t start_time = SDL_GetTicks();
	int frame_count	    = 0;

	{
		std::fstream fs("res.astar", std::ios::out | std::ios::binary);

		if (!fs) {
			std::cerr << "Failed to open file for writing!\n";
			return -1;
		}

		cereal::BinaryOutputArchive archive(fs);

		archive(game);

		fs.flush();
		fs.close();
	}

	while (!quit) {

		uint64_t current_time = SDL_GetTicks();
		frame_count++;

		uint64_t current_ticks = SDL_GetTicks();
		delta_time	       = (current_ticks - previous_ticks) / 1000.0f; // Convert milliseconds to seconds
		previous_ticks	       = current_ticks;

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		SDL_RenderClear(renderer);

		// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		const bool* keyboard_state = SDL_GetKeyboardState(NULL);

		Uint32 mouse_state = SDL_GetMouseState(&MOUSE_POS_X, &MOUSE_POS_Y);
		get_pressed_keys(keyboard_state, mouse_state, gamepad_state);
		const bool* keystate = SDL_GetKeyboardState(NULL);

		game.process(get_pressed_keys(keyboard_state, mouse_state, gamepad_state));

		if (keystate[SDL_SCANCODE_LEFT]) {
			game.scenes["test"].objects[0].position_x -= 50 * delta_time;
		}

		if (keystate[SDL_SCANCODE_RIGHT]) {
			game.scenes["test"].objects[0].position_x += 50 * delta_time;
		}

		if (keystate[SDL_SCANCODE_UP]) {
			game.scenes["test"].objects[0].position_y -= 50 * delta_time;
		}

		if (keystate[SDL_SCANCODE_DOWN]) {
			game.scenes["test"].objects[0].position_y += 50 * delta_time;
		}

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
