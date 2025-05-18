#include "eadkpp.h"
#include "hat.h"
using namespace EADK;

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Calculation";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

const Color ORANGE = Color(0xFFB531);

void draw() {
    Display::drawString("UK", Point(74, 3), false, Color(0xFFFFFF), ORANGE);
    Display::pushRect(Rect(93, 4, 18, 9), IMAGE);
}

int main(int argc, char * argv[]) {
    draw();
    while (1) {}
}
