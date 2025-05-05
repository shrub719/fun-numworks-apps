#include <cmath>
#include "object.h"

void matrixMul() {

}

void rotatePoint() {

}

Object::Object() {
    for (int i = 0; i < 32; i++) {
        points[i][0] = sin(i*0.2);
        points[i][1] = cos(i*0.2);
        points[i][2] = -0.15f;
    }
    for (int i = 32; i < 62; i++) {
        points[i][0] = points[i-32][0];
        points[i][1] = points[i-32][1];
        points[i][2] = 0.15f;
    }
}

void Object::rotate(float (&matrix)[3][3]) {
    for ()
}

void Object::draw() {

}

void Object::erase() {

}
