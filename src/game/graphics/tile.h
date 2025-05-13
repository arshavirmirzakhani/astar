enum BLEND_TYPES{
    ADD,
    SUBTRACT,
    AVERAGE,
};

class Tile {
    private:
        // 8 x 8 grid with numbers in range of [0,255] , zero is blank
        unsigned char colors[64] = {0}; 

        // blend values are used to create sprite effects like fading black/white (you can think of them as some kind of shader)
        unsigned char blend_color[64] = {0}; 

        // how blend values effect color values)
        BLEND_TYPES blend_type[64] = {ADD}; 

    public:
        Tile();
        ~Tile();
};


