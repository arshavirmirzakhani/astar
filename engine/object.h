#pragma once
#include <string>
#include <vector>
#include <map>
#include "graphics/sprite.h"

class Object {
    public:
        Object(std::string type);
        ~Object();

        std::string type_name;
        unsigned int current_frame;
        int frame_per_tick; 
        std::string current_animation_state;
        std::map<std::string, std::vector<Sprite>> all_sprites;

};


