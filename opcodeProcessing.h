#include <iostream>
#include <sstream>
#include <stack>
#include "stateData.h"

using namespace std;

void determineInstruction(CHIP8state &currState);

void process0x8000Codes(CHIP8state &currState, short opcode);
void process0xF000Codes(CHIP8state &currState, short opcode);
