#include "stateData.h"

CHIP8state::CHIP8state(string fn) : PC(512), I(0), filename(fn), delayTimer(0), soundTimer(0)
{
}
