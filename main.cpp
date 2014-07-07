#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include "opcodeProcessing.h"

using namespace std;

// TODO: Don't hardcode the ROM path!

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

int main(int, char **)
{
   CHIP8state currState("../c8games/PONG");
   readRom("../c8games/PONG", currState);
   while (currState.PC >= 512 && currState.PC < 4096)
   {
      determineInstruction(currState);
      cout << "currState.PC = " << hex << currState.PC << endl;
   }
   // stuff
   return 0;
}
