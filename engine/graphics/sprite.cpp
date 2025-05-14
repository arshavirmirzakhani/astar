#include "sprite.h"

Sprite::Sprite(unsigned int width,unsigned int height) {

    this->width = width;
    this->height = height;

    this->sprite_buffer = new unsigned char[(this->width * 8) * this->height];
}

Sprite::~Sprite() {
    delete[] this->sprite_buffer;
}

void Sprite::set_buffer(unsigned char *buffer) {
    this->sprite_buffer = buffer;
}


unsigned char* Sprite::render(int sprite_Xy,int sprite_y) {

    std::vector<unsigned char> buffer;

    for (int y=0; y < SCREEN_HEIGHT; y++){     
        for (int x=0; x < SCREEN_WIDTH; x++){
            if (x >= sprite_Xy&& x <= sprite_Xy + this->width && y >= sprite_y && y <= sprite_y + this->height) {
                buffer.push_back(this->sprite_buffer[(y*width)+x]);
            }
        }   
    }

    return buffer.data();

}
