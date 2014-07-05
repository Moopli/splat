#include "stateData.h"

CHIP8state::CHIP8state(string fn) : I(0), PC(512), delayTimer(0), soundTimer(0), filename(fn)
{
}
