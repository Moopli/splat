#include "stateData.h"
#include <CImg.h>
using namespace cimg_library;

CHIP8state::CHIP8state(string fn) : I(0), PC(512), delayTimer(0), soundTimer(0), filename(fn)
{
   // this->cDisplay = new CImgDisplay(64, 32, "", 3, false, false);
   // Make the display start out blank when ROM is loaded.
   for (int j = 0; j < 32; j++)
   {
      for (int i = 0; i < 64; i++)
      {
         this->display[i][j] = false;
      }
   }
}
