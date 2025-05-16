#pragma once
#include "../global.h"
#include <vector>
class Sprite {
    private:
    public:
        std::vector<unsigned char> sprite_buffer;

        Sprite(unsigned int width,unsigned int height);
        ~Sprite();

        unsigned int width;
        unsigned int height;

        unsigned char* render(int sprite_x,int sprite_y);
};


