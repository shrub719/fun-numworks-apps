#include "storage.h"
#include "eadkpp.h"
#include <eadk.h>

using namespace EADK;

void save_canvas(int id) {
    eadk_color_t currentCanvas[320 * 240];
    eadk_display_pull_rect(Screen::Rect, currentCanvas);
    
}

void load_canvas(int id) {

}