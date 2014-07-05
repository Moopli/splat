#include "stateData.h"

using namespace std;

void determineInstruction(CHIP8state &currState);

int getNibbleAt(uint16_t opcode, int pos);
int getFirstNibble(uint16_t opcode);
int getSecondNibble(uint16_t opcode);
int getThirdNibble(uint16_t opcode);
int getLastNibble(uint16_t opcode);
uint16_t getLastThreeNibbles(uint16_t opcode);

unsigned char getLastByte(uint16_t opcode);

void process0x8000Codes(CHIP8state &currState, uint16_t opcode);
void process0xF000Codes(CHIP8state &currState, uint16_t opcode);
