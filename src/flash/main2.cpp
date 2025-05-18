#include "eadkpp.h"
#include "main.h"
using namespace EADK;

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Flashlight";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;


int main(int argc, char * argv[]) {
    Keyboard::State keyboardState = Keyboard::scan();
    laplace_init();
    led_init();
    set_led_blue(true);
    while (!keyboardState.keyDown(Keyboard::Key::Back)) {
        keyboardState = Keyboard::scan();
    }
}
