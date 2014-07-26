#pragma once

#include <cstdint>
#include "stateData.h"
#include <CImg.h>

using namespace std;
using namespace cimg_library;

void determineInstruction(CHIP8state &currState);

int getNibbleAt(uint16_t opcode, int pos);
int getFirstNibble(uint16_t opcode);
int getSecondNibble(uint16_t opcode);
int getThirdNibble(uint16_t opcode);
int getLastNibble(uint16_t opcode);
uint16_t getLastThreeNibbles(uint16_t opcode);

static int key_mappings[] = {cimg::keyB, cimg::key4, cimg::key5, cimg::key6,\
                    cimg::keyR, cimg::keyT, cimg::keyY, cimg::keyF,\
                    cimg::keyG, cimg::keyH, cimg::keyV, cimg::keyN,\
                    cimg::key7, cimg::keyU, cimg::keyJ, cimg::keyM};

unsigned char getLastByte(uint16_t opcode);

void process0x8000Codes(CHIP8state &currState, uint16_t opcode);
void process0xF000Codes(CHIP8state &currState, int x, int kk);
