#include "game/game.h"
#include <SDL3/SDL.h>

const int VIRTUAL_WIDTH = 160;
const int VIRTUAL_HEIGHT = 144;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Fixed Screen Size", 640, 480, SDL_WINDOW_RESIZABLE);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    Game game_obj("my game");

    // Set the logical size: this is your fixed screen size
    SDL_SetRenderLogicalPresentation(renderer, VIRTUAL_WIDTH, VIRTUAL_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw a red rectangle to demonstrate scaling
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_FRect rect1 = { 10, 10, 100, 100 }; // Logical coordinates
        SDL_RenderFillRect(renderer, &rect1);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_FRect rect2 = { 90, 90, 100, 100 }; // Logical coordinates
        SDL_RenderFillRect(renderer, &rect2);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
