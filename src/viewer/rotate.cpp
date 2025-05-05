#include "eadkpp.h"
#include "trig.h"
using namespace EADK;

const float s = approx_sin(0.05);
const float c = approx_cos(0.05);

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

void get_rotation(float (&matrix)[3][3], Keyboard::State keyboardState) {
    float r[3][3] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, c, -s},
        {0.0f, s, c}
    };
    if (keyboardState.keyDown(Keyboard::Key::Up)) {
        matrix_mul(r, matrix);
    }
}
