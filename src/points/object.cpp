#include "eadkpp.h"
#include "display.h"
#include "object.h"
#include "trig.h"
using namespace EADK;

// replaces a point with its rotation under the current matrix
void rotate_point(float (&point)[3], float (&matrix)[3][3]) {  // don't ask why the references are like that
    float result[3];
    for (int i = 0; i < 3; ++i) {
        result[i] = 0.0f;
        for (int j = 0; j < 3; ++j) {
            result[i] += matrix[i][j] * point[j];
        }
    }
    point[0] = result[0];
    point[1] = result[1];
    point[2] = result[2];
}

Object::Object() {   // default object
    load_object(2);  // (a green-ish cube)
    color[0] = 0.0f;
    color[1] = 1.0f;
    color[2] = 0.5f;
    scale = 50;
    size = 15;
    to_coords();
}

// loads objects using for loops, so the points themselves don't always have to be stored in memory
void Object::load_object(int id) {
    switch (id) {
        case 1:  // donut
            length = 128;
            for (int i = 0; i < 64; i++) {
                float t = i * 0.1f;
                points[i][0] = better_sin(t);
                points[i][1] = better_cos(t);
                points[i][2] = -0.15f;
            }
            for (int i = 64; i < 128; i++) {
                points[i][0] = points[i-64][0];
                points[i][1] = points[i-64][1];
                points[i][2] = 0.15f;
            }
            break;
        case 2:  // cube
            int i = 0;
            for (int a = -1; a <= 1; a += 2) {
                for (int b = -1; b <= 1; b += 2) {
                    for (float c = -1.0f; c <= 1.0f; c += 0.2f) {
                        points[i][0] = a;
                        points[i][1] = b;
                        points[i][2] = c;
                        i++;
                        points[i][0] = a;
                        points[i][1] = c;
                        points[i][2] = b;
                        i++;
                        points[i][0] = c;
                        points[i][1] = a;
                        points[i][2] = b;
                        i++;
                    }
                }
            }
            length = i;
    }
}

// rotates each point in the object one-by-one
// also insorts points by ascending z-coordinate so that the front ones draw last/on top
void Object::rotate(float (&matrix)[3][3]) {
    rotate_point(points[0], matrix);
    for (int i = 1; i < length; i++) {
        rotate_point(points[i], matrix);
        float key[3] = {points[i][0], points[i][1], points[i][2]};
        int j = i - 1;

        while (j >= 0 && points[j][2] > key[2]) {
            points[j + 1][0] = points[j][0];
            points[j + 1][1] = points[j][1];
            points[j + 1][2] = points[j][2];
            j -= 1;
        }
        points[j + 1][0] = key[0];
        points[j + 1][1] = key[1];
        points[j + 1][2] = key[2];
    }
}

// turns the points array of normalised floats into coordinates on the screen
// run on the entire list before drawing, storing it in the coords property
// - it draws faster but requires essentially storing the array twice. good idea? [!]
void Object::to_coords() {
    for (int i = 0; i < length; i++) {
        int x = 160 + scale * points[i][0];
        int y = 120 + scale * points[i][1];
        int c = (points[i][2] + 3) / 5 * 255;
        coords[i][0] = x;
        coords[i][1] = y;
        coords[i][2] = c;
    }
}

// iterates over the coordinates and draws them on the screen according to scale, size and color
void Object::draw() {
    int s = size / 2;
    to_coords();
    for (int i = 0; i < length; i++) {
        int x = coords[i][0];
        int y = coords[i][1];
        int c = coords[i][2];
        int r = color[0] * c;
        int g = color[1] * c;
        int b = color[2] * c;
        int value = r * 65536 + g * 256 + b;
        Display::pushRectUniform(Rect(x-s, y-s, size, size), Color(value));
    }
}

// checks input for any property changes (scale, size, object, color)
bool Object::get_properties(Keyboard::State keyboardState) {
    bool update = false;

    // scale
    if (keyboardState.keyDown(Keyboard::Key::Plus)) {
        update = true;
        scale += 1;
    }
    if (keyboardState.keyDown(Keyboard::Key::Minus)) {
        update = true;
        scale -= 1;
    }
    
    // size
    if (keyboardState.keyDown(Keyboard::Key::Multiplication)) {
        update = true;
        size += 1;
    }
    if (keyboardState.keyDown(Keyboard::Key::Division)) {
        update = true;
        size -= 1;
    }

    // object type
    if (keyboardState.keyDown(Keyboard::Key::One)) {
        update = true;
        load_object(1);
    } else if (keyboardState.keyDown(Keyboard::Key::Two)) {
        update = true;
        load_object(2);
    }

    // color
    float speed = 0.05f;
    if (keyboardState.keyDown(Keyboard::Key::Pi)) {
        update = true;
        color_edit(0, -speed);
    } else if (keyboardState.keyDown(Keyboard::Key::Imaginary)) {
        update = true;
        color_edit(0, speed);
    }
    if (keyboardState.keyDown(Keyboard::Key::Sqrt)) {
        update = true;
        color_edit(1, -speed);
    } else if (keyboardState.keyDown(Keyboard::Key::Comma)) {
        update = true;
        color_edit(1, speed);
    }
    if (keyboardState.keyDown(Keyboard::Key::Square)) {
        update = true;
        color_edit(2, -speed);
    } else if (keyboardState.keyDown(Keyboard::Key::Power)) {
        update = true;
        color_edit(2, speed);
    }

    return update;
}

// increases/decreases color ensuring no under/overflow
// [!] would it be better to store colour as eadk_color_t?
void Object::color_edit(int value, float increaseBy) {
    color[value] += increaseBy;
    if (color[value] <= 0.0f) {
        color[value] = 0.0f;
    } else if (color[value] >= 1.0f) {
        color[value] = 1.0f;
    }
}
