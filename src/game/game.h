#pragma once
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include "object.h"
#include "global.h"

class Game {

    private:
        std::vector<Object> objects;
        
        
        public:
        Game(std::string name);
        ~Game();
        
        std::string name;
        char engine_version[3] = {0};
        std::vector<unsigned char> screen_buffer; 

        void process();
        void render();

        void add_object(Object object);
};

