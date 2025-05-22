#include "storage.h"
#include "eadkpp.h"
#include "canvas.h"
#include <eadk.h>

using namespace EADK;

void Canvas::save_canvas(int id) {
    for (int row = 0; row < height; row++) {
        eadk_display_pull_rect(Rect(0, (row * 2 + 18), width, 2), save_buffer);
        
    }
}

void Canvas::load_canvas(int id) {

}