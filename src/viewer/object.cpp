#include "eadkpp.h"
#include "display.h"
#include "object.h"
#include "trig.h"
using namespace EADK;

void rotate_point(float (&point)[3], float (&matrix)[3][3]) {
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

Object::Object() {
    length = 62;
    for (int i = 0; i < 32; i++) {
        float t = i * 0.2f;
        points[i][0] = approx_sin(t);
        points[i][1] = approx_cos(t);
        points[i][2] = -0.15f;
    }
    for (int i = 32; i < 62; i++) {
        points[i][0] = points[i-32][0];
        points[i][1] = points[i-32][1];
        points[i][2] = 0.15f;
    }
    scale = 50;
    size = 5;
    to_coords();
}

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

void Object::draw() {
    int s = size / 2;
    to_coords();
    for (int i = 0; i < length; i++) {
        int x = coords[i][0];
        int y = coords[i][1];
        int c = coords[i][2];
        int color = c * 65536 + c * 256 + c;
        Display::pushRectUniform(Rect(x-s, y-s, size, size), Color(color));
    }
}

bool Object::get_properties(Keyboard::State keyboardState) {
    bool update = false;

    if (keyboardState.keyDown(Keyboard::Key::Plus)) {
        update = true;
        scale += 1;
    }
    if (keyboardState.keyDown(Keyboard::Key::Minus)) {
        update = true;
        scale -= 1;
    }
    if (keyboardState.keyDown(Keyboard::Key::Multiplication)) {
        update = true;
        size += 1;
    }
    if (keyboardState.keyDown(Keyboard::Key::Division)) {
        update = true;
        size -= 1;
    }

    return update;
}
