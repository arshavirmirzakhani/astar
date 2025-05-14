#include "object.h"

class Scene {
    public:

        std::vector<Object> objects;

        Scene();
        ~Scene();

        void add_object(Object object);
    };


