#include "eadkpp.h"
#include "ui.h"
using namespace EADK;

Cursor::Cursor() {
    x = 320 / 2;
    y = 222 / 2;
    for (int i = 0; i < cLength; i++) {
        covering[i][0] = 255;
        covering[i][1] = 255;
        covering[i][2] = 255; 
    }
    draw();
}

void Cursor::move(int dx, int dy) {

}

void Cursor::update_covering() {

}

void Cursor::draw(bool erase) {

}

Bar::Bar() {
    color = BLACK;
}

void Bar::update_color(cursorColor newColor) {

}

void Bar::update_message(char text[]) {

}
