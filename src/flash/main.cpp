#include "eadkpp.h"
using namespace EADK;

#define SVC_ATTRIBUTES __attribute__((noinline, externally_visible))
#define SVC_RETURNING_VOID(code) \
  asm volatile("svc %[immediate]" : : [immediate] "I"(code));

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Flashlight";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

void SVC_ATTRIBUTES setColor(Color c) {
    asm volatile("mov r0, %0" : : "r"(c));
    SVC_RETURNING_VOID(37)
}

void SVC_ATTRIBUTES setLock(bool locked) {
    asm volatile("mov r0, %0" : : "r"(locked));
    SVC_RETURNING_VOID(58)
}

void SVC_ATTRIBUTES setBlinking(uint16_t periodInMilliseconds, float dutyCycle) {
    SVC_RETURNING_VOID(36)
}


int main(int argc, char * argv[]) {
    Keyboard::State keyboardState = Keyboard::scan();
    Color white = Color(0xFFFFFF);

    setColor(white);

    while (!keyboardState.keyDown(Keyboard::Key::Back)) {
        keyboardState = Keyboard::scan();
        setColor(white);
    }
}
