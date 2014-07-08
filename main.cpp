#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>
#include "opcodeProcessing.h"

using namespace std;

// TODO: Don't hardcode the ROM path!

void fillDigitSprites(CHIP8state &currState);

void readRom(const string &filename, CHIP8state &currState)
{
   ifstream fin(filename, ios::binary);
   istreambuf_iterator<char> first(fin); // buf for unformatted extractions

   // copy file to RAM starting at PC until 0x1FFF
   copy_n(first, currState.RAM.size() - currState.PC, currState.RAM.data() + currState.PC);

   // make sure that EOF was reached (or there's only whitespace left)
   if (!(fin >> ws).eof())
   {
      throw runtime_error("ROM is too big.");
   }
}

int main(int argc, char **argv)
{
   vector<string> args(argv, argv + argc);
   string filename = (args.size() > 1) ? args[1] : "../c8games/PONG";

   CHIP8state currState(filename);
   readRom(filename, currState);
   fillDigitSprites(currState);
   while (currState.PC >= 512 && currState.PC < 4096)
   {
      determineInstruction(currState);
      cout << "currState.PC = " << hex << currState.PC << endl;
   }
   // stuff
   return 0;
}

void fillBytes(unsigned char *start, initializer_list<unsigned char> bytes)
{
   copy(begin(bytes), end(bytes), start);
}

void fillDigitSprites(CHIP8state &currState)
{
   fillBytes(&currState.RAM[0], {0xF0, 0x90, 0x90, 0x90, 0xF0});  // 0
   fillBytes(&currState.RAM[5], {0x20, 0x60, 0x20, 0x20, 0x70});  // 1
   fillBytes(&currState.RAM[10], {0xF0, 0x10, 0xF0, 0x80, 0xF0}); // 2
   fillBytes(&currState.RAM[15], {0xF0, 0x10, 0xF0, 0x10, 0xF0}); // 3
   fillBytes(&currState.RAM[20], {0x90, 0x90, 0xF0, 0x10, 0x10}); // 4
   fillBytes(&currState.RAM[25], {0xF0, 0x80, 0xF0, 0x10, 0xF0}); // 5
   fillBytes(&currState.RAM[30], {0xF0, 0x80, 0xF0, 0x90, 0xF0}); // 6
   fillBytes(&currState.RAM[35], {0xF0, 0x10, 0x20, 0x40, 0x40}); // 7
   fillBytes(&currState.RAM[40], {0xF0, 0x90, 0xF0, 0x90, 0xF0}); // 8
   fillBytes(&currState.RAM[45], {0xF0, 0x90, 0xF0, 0x10, 0xF0}); // 9
   fillBytes(&currState.RAM[50], {0xF0, 0x90, 0xF0, 0x90, 0x90}); // A
   fillBytes(&currState.RAM[55], {0xE0, 0x90, 0xE0, 0x90, 0xE0}); // B
   fillBytes(&currState.RAM[60], {0xF0, 0x80, 0x80, 0x80, 0xF0}); // C
   fillBytes(&currState.RAM[65], {0xE0, 0x90, 0x90, 0x90, 0xE0}); // D
   fillBytes(&currState.RAM[70], {0xF0, 0x80, 0xF0, 0x80, 0xF0}); // E
   fillBytes(&currState.RAM[75], {0xF0, 0x80, 0xF0, 0x80, 0x80}); // F
}