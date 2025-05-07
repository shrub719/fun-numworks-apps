#include "eadkpp.h"

class Object {
    public:
        Object();
        void load_object(int id);
        void rotate(float (&matrix)[3][3]);
        void to_coords();
        void draw();
        bool get_properties(EADK::Keyboard::State keyboardState);
        void color_edit(int value, float increaseBy);
    private:
        float points[200][3];
        int coords[200][3];
        float color[3];
        int length;
        int scale;
        int size;
};