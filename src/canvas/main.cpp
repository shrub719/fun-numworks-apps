#include "eadkpp.h"
using namespace EADK;

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Canvas";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

int main(int argc, char * argv[]) {
    Keyboard::State keyboardState = Keyboard::scan();

    Display::pushRectUniform(Screen::Rect, Color(0xFFFFFF));
    while (!keyboardState.keyDown(Keyboard::Key::Back)) {

    }
}
