#include "eadkpp.h"
#include "trig.h"
using namespace EADK;

// const float a = 0.05;
// const float s = approx_sin(a);
// const float c = approx_cos(a);

/* 
def matrix_mul(A, B):
    result = [tuple(sum(a*b for a,b in zip(A_row,B_col)) for B_col in zip(*B)) for A_row in A]
    return result
*/
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

    bool update = false;
    float s = approx_sin(0.05f);
    float c = approx_cos(0.05f);

    if (keyboardState.keyDown(Keyboard::Key::Up)) {
        update = true;
        float r[3][3] = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, c, -s},
            {0.0f, s, c}
        };
        matrix_mul(r, matrix);
    }
    if (keyboardState.keyDown(Keyboard::Key::Right)) {
        update = true;
        float r[3][3] = {
            {c, 0.0f, s},
            {0.0f, 1.0f, 0.0f},
            {-s, 0.0f, c}
        };
        matrix_mul(r, matrix);
    }

    return update;
}
