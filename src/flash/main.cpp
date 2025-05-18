#include "eadkpp.h"
using namespace EADK;

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Flashlight";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

void SVC_RETURNING_VOID(int code) {
    asm volatile("svc %[immediate]" : : [immediate] "I"(code));
}

void __attribute__((noinline, externally_visible)) setColor(Color c) {
    SVC_RETURNING_VOID(37);
}

void __attribute__((noinline, externally_visible)) setLock(bool locked) {
    SVC_RETURNING_VOID(58);
}

void __attribute__((noinline, externally_visible)) setBlinking(uint16_t periodInMilliseconds, float dutyCycle) {
    SVC_RETURNING_VOID(36);
}


int main(int argc, char * argv[]) {
    Keyboard::State keyboardState = Keyboard::scan();
    Color white = Color(0xFFFFFF);

    setLock(false);
    setColor(white);
    setBlinking(1000, 0.1f);

    while (!keyboardState.keyDown(Keyboard::Key::Back)) {
        keyboardState = Keyboard::scan();
    }
}
