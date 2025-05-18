#include "eadkpp.h"
#include "save-load.h"
using namespace EADK;

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Canvas";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

int main(int argc, char * argv[]) {
    Keyboard::State keyboardState = Keyboard::scan();

    Display::pushRectUniform(Screen::Rect, Color(0xFFFFFF));
    
    while (!keyboardState.keyDown(Keyboard::Key::Back)) {
        keyboardState = Keyboard::scan();
    }
    save_canvas(1);     // crashes calculator sometimes
                        // (why sometimes? don't tell me garbage collection is still an issue)
    while (!keyboardState.keyDown(Keyboard::Key::One)) {
        keyboardState = Keyboard::scan();
    }
}
