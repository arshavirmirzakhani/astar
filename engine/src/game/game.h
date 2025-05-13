#pragma once
#include <string>
#include <vector>
#include <map>
#include <SDL3/SDL.h>
#include "object.h"
#include "global.h"

struct Color {
    unsigned char r, b, g = 0;
    unsigned char a = 255;
};

struct Pallete {
    Color colors[255];
};

class Game {
  
    public:
        Game(std::string name);
        ~Game();

        std::string name;
        char engine_version[3] = {0};

        std::vector<Object> objects;
        
        std::vector<unsigned char> screen_buffer; 

        unsigned int current_pallete = 0;
        std::map<unsigned int,Pallete> color_pallets;

        void process();
        void render();

        void add_object(Object object);
};

