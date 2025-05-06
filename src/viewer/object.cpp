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
    load_object(2);
    color[0] = 0.0f;
    color[1] = 1.0f;
    color[2] = 0.2f;
    scale = 50;
    size = 25;
    to_coords();
}

void Object::load_object(int id) {
    switch (id) {
        case 1:
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
            break;
        case 2:
            int i = 0;
            for (int a = -1; a <= 1; a += 2) {
                for (int b = -1; b <= 1; b += 2) {
                    for (float c = -1.0f; c <= 1.0f; c += 0.4f) {
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
        int r = color[0] * c;
        int g = color[1] * c;
        int b = color[2] * c;
        int value = r * 65536 + g * 256 + b;
        Display::pushRectUniform(Rect(x-s, y-s, size, size), Color(value));
    }
}

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

void Object::color_edit(int value, float increaseBy) {
    color[value] += increaseBy;
    if (color[value] <= 0.0f) {
        color[value] = 0.0f;
    } else if (color[value] >= 1.0f) {
        color[value] = 1.0f;
    }
}
