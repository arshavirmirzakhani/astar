#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include "object.h"

class Game {

    private:
        std::vector<Object> objects;


    public:
        Game(std::string name);
        ~Game();
        void add_object(Object object);
};

