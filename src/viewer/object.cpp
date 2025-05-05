#include "eadkpp.h"
#include "display.h"
#include "object.h"
#include "trig.h"
using namespace EADK;


/* 
def rotate_point(rotation, coordinate):
    result = tuple(sum(a * b for a, b in zip(row, coordinate)) for row in rotation)
    return result
*/
void rotate_point(float (&point)[3], float (&matrix)[3][3]) {
    float result[3];
    for (int i = 0; i < 3; i++) {
        int sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += point[j] * matrix[i][j];
        }
        result[i] = sum;
    }
    point[0] = result[0];
    point[1] = result[1];
    point[2] = result[2];
}

Object::Object() {
    for (int i = 0; i < 32; i++) {
        float t = i * 0.2f;
        points[i][0] = std::sin(t);
        points[i][1] = std::cos(t);
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
    for (float (&point)[3] : points) {
        rotate_point(point, matrix);
    }
}

/*
def to_coords(point, scale):
    x = X + scale * point[0]
    y = Y + scale * point[1]
    c = (point[2] + 3) / 5 * 255
    return round(x), round(y), (COLOUR[0]*c, COLOUR[1]*c, COLOUR[2]*c)


s = size // 2
    coords = [to_coords(point, scale) for point in obj]
    for x, y, c in coords:
        fill_rect(x-s, y-s, size, size, c)
*/
void Object::to_coords() {
    for (int i = 0; i < 62; i++) {
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
    for (int (&coord)[3] : coords) {
        int x = coord[0];
        int y = coord[1];
        int c = coord[2];
        Display::pushRectUniform(Rect(x-s, y-s, size, size), Color(0x000000));
    }
}

void Object::erase() {

}
