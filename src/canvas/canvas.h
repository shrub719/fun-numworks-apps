#ifndef CANVAS_H
#define CANVAS_H

#include "eadkpp.h"
#include <eadk.h>

class Canvas {
    public:
        void save_canvas(int id);
        void load_canvas(int id);
    private:
        static const int height = (EADK::Screen::Height - 18) / 2;
        static const int width = EADK::Screen::Width / 2;
        eadk_color_t save_buffer[width];
};

#endif
