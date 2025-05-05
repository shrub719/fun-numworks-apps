#include "eadkpp.h"

class Object {
    public:
        Object();
        void rotate(float (&matrix)[3][3]);
        void to_coords();
        void draw();
        void erase();
        void get_properties(EADK::Keyboard::State keyboardState);
    private:
        float points[62][3];
        int coords[62][3];
        int scale;
        int size;
};