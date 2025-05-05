#include "eadkpp.h"

class Object {
    public:
        Object();
        void load_object(int id);
        void rotate(float (&matrix)[3][3]);
        void to_coords();
        void draw();
        bool get_properties(EADK::Keyboard::State keyboardState);
    private:
        float points[70][3];
        int coords[70][3];
        int length;
        int scale;
        int size;
};