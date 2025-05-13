#pragma once
#include "../global.h"
#include <vector>
class Sprite {
    private:
        unsigned char *sprite_buffer;
    public:

        Sprite(unsigned int width,unsigned int height);
        ~Sprite();

        unsigned int width;
        unsigned int height;

        unsigned char* render(int sprite_x,int sprite_y);

        void set_buffer(unsigned char *sprite_buffer);
};


