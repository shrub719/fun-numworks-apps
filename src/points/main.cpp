#include "display.h"
#include "eadkpp.h"
#include "object.h"
#include "rotate.h"
#include <eadk.h>
// eadk.h is required for eadk_display_wait_for_vblank
using namespace EADK;

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "3D Points";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;  // i don't know what this does but it's always 0

int main(int argc, char * argv[]) {
    Object object;
    bool rotationUpdate, propertyUpdate;
    float matrix[3][3] {     // one static matrix for all rotation calculations
        {1.0f, 0.0f, 0.0f},  // memory efficiency isn't that much of a problem i just felt like it
        {0.0f, 1.0f, 0.0f},  // starts as an identity matrix (no rotation)
        {0.0f, 0.0f, 1.0f}
    };
    Keyboard::State keyboardState = Keyboard::scan();

    Display::pushRectUniform(Screen::Rect, Color(0xFFFFFF));
    object.draw();
    while (!keyboardState.keyDown(Keyboard::Key::Home)) {
        keyboardState = Keyboard::scan();
        rotationUpdate = get_rotation(matrix, keyboardState);
        propertyUpdate = object.get_properties(keyboardState);
        if (rotationUpdate || propertyUpdate) {  // boolean flags if an update happened
            object.rotate(matrix);
            Display::pushRectUniform(Screen::Rect, Color(0xFFFFFF));
            object.draw();
        }
        eadk_display_wait_for_vblank();  // stops the weird flashing
    }
}
