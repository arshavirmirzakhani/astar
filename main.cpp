#include <iostream>
#include <SDL3/SDL.h>

int main(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
 
    SDL_Quit();
    
    std::cout << "SDL is working "<< std::endl;
    return 0;
}