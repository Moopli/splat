#include "stateData.h"

struct CHIP8state;

CHIP8state::CHIP8state() : PC(512), I(0), filename(""), delayTimer(0), soundTimer(0)
{
   this->keys = new bool[16];
   this->V = new short[16];
   this->RAM = new unsigned char[4096];
}

CHIP8state::CHIP8state(string fn) : PC(512), I(0), filename(fn), delayTimer(0), soundTimer(0)
{
   this->keys = new bool[16];
   this->V = new short[16];
   this->RAM = new unsigned char[4096];
}
CHIP8state::~CHIP8state()
{
   delete this->keys;
   delete this->V;
   delete this->RAM;
}
