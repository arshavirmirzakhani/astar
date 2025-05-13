#include "game.h"

Game::Game(std::string name) {
    SDL_LogInfo(SDL_LogCategory::SDL_LOG_CATEGORY_TEST,(name + std::string(" is running")).c_str());
}

Game::~Game() {
    SDL_LogInfo(SDL_LogCategory::SDL_LOG_CATEGORY_TEST,"DIE!");
}


void Game::add_object(Object object) {
    this->objects.push_back(object);
}