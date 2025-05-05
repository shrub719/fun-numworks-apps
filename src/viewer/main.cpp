#include "display.h"
#include "eadkpp.h"
#include "object.h"
#include "rotate.h"
using namespace EADK;

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "3D Viewer";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;  // i don't know what this does

int main(int argc, char * argv[]) {
    Object object;
    bool update;
    float matrix[3][3] {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };
    Keyboard::State keyboardState = Keyboard::scan();

    Display::pushRectUniform(Screen::Rect, Color(0xFFFFFF));
    object.draw();
    while (!keyboardState.keyDown(Keyboard::Key::Back)) {
        keyboardState = Keyboard::scan();
        update = get_rotation(matrix, keyboardState);
        object.get_properties(keyboardState);
        if (update) {
            object.rotate(matrix);
            Display::pushRectUniform(Screen::Rect, Color(0xFFFFFF));
            object.draw();
        }
        Timing::msleep(20);
    }
}
