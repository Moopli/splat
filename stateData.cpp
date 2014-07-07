#include "stateData.h"

CHIP8state::CHIP8state(string fn) : I(0), PC(512), delayTimer(0), soundTimer(0), filename(fn)
{
   // Make the display start out blank when ROM is loaded.
   for (int j = 0; j < 32; j++)
   {
      for (int i = 0; i < 64; i++)
      {
         this->display[i][j] = false;
      }
   }
}
