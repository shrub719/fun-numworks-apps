#include "eadkpp.h"
#include "trig.h"
using namespace EADK;

// 3x3 * 3x3 matrix multipication for rotation matrices
void matrix_mul(float (&multiplier)[3][3], float (&matrix)[3][3]) {
    float result[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float sum = 0.0f;
            for (int k = 0; k < 3; k++) {
                sum += multiplier[i][k] * matrix[k][j];
            }
            result[i][j] = sum;
        }
    }

    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = result[i][j];
        }
    }
}

// checks input for any rotations, returning a bool flag if there were any rotations + puts the rotations in the input array
bool get_input(int (&input)[3], Keyboard::State keyboardState) {  // again, don't ask about references
    int x = 0;
    int y = 0;
    int z = 0;
    
    // pitch
    if (keyboardState.keyDown(Keyboard::Key::Up)) {
        x = 1;
    } else if (keyboardState.keyDown(Keyboard::Key::Down)) {
        x = -1;
    }
    // yaw
    if (keyboardState.keyDown(Keyboard::Key::Right)) {
        y = 1;
    } else if (keyboardState.keyDown(Keyboard::Key::Left)) {
        y = -1;
    }
    // roll
    if (keyboardState.keyDown(Keyboard::Key::Alpha)) {
        z = 1;
    } else if (keyboardState.keyDown(Keyboard::Key::Shift)) {
        z = -1;
    }
    
    input[0] = x;
    input[1] = y;
    input[2] = z;

    return (x != 0) || (y != 0) || (z != 0);
}

// checks input for rotations using get_input
// creates a rotation matrix by multiplying each of the rotations together, then uses that to rotate every point
bool get_rotation(float (&matrix)[3][3], Keyboard::State keyboardState) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                matrix[i][j] = 1.0f;
            } else {
                matrix[i][j] = 0.0f;
            }
        }
    }
    
    int input[3];
    bool update = get_input(input, keyboardState);
    float S = approx_sin(0.02f);
    float C = approx_cos(0.02f);

    if (input[0] != 0) {
        float s = S;
        float c = C;
        if (input[0] == -1) {
            s = -s;
        }

        float r[3][3] = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, c, -s},
            {0.0f, s, c}
        };
        matrix_mul(r, matrix);
    }
    if (input[1] != 0) {
        float s = S;
        float c = C;
        if (input[1] == -1) {
            s = -s;
        }

        float r[3][3] = {
            {c, 0.0f, s},
            {0.0f, 1.0f, 0.0f},
            {-s, 0.0f, c}
        };
        matrix_mul(r, matrix);
    }
    if (input[2] != 0) {
        float s = S;
        float c = C;
        if (input[2] == -1) {
            s = -s;
        }

        float r[3][3] = {
            {c, -s, 0.0f},
            {s, c, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        matrix_mul(r, matrix);
    }

    return update;
}
