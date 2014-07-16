#include "stateData.h"
#include <CImg.h>
using namespace cimg_library;

CHIP8state::CHIP8state(string fn)
    : I(0), PC(512), delayTimer(0), soundTimer(0), display{}, filename(fn) {
    this->cDisplay = new CImgDisplay(64 * 4, 32 * 4, "", 3, false, false);
}
