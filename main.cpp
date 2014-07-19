#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>
#include "opcodeProcessing.h"
#include <CImg.h>
#include <ctime>

using namespace std;
using namespace cimg_library;

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

bool goToNextInstruction(double & prevTime, clock_t & start, const double period)
{
   cout << "\n\nPeriod = " << period << "\n\n";
   double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
   if ((duration - prevTime) >= period)
   {
      prevTime = duration;
      return true;
   }
   return false;
}

bool changeTimer(int & dTimer, clock_t & start, double & prevTime)
{
   double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
   cout << "duration = " << duration << "\nprevTime = " << prevTime << endl;
   if ((duration - prevTime) >= 1)
   {
      dTimer--;
      prevTime = duration;
      return true; // Yes, delay timer was changed
   }
   return false; // No, delay timer is the same
}

void runRom(string filename, double frequency)
{
   CHIP8state currState(filename);
   readRom(filename, currState);
   fillDigitSprites(currState);
   clock_t start = std::clock();
   double period = (double)(1 / (double)frequency);
   double prevTime = 0;
   double continuePrevTime = 0;
   while (currState.PC >= 512 && currState.PC < 4096 && !currState.cDisplay->is_closed())
   {
      if (currState.delayTimer > 0)
      {
         (void)changeTimer(currState.delayTimer, start, prevTime);
      }
      if (goToNextInstruction(continuePrevTime, start, period))
      {
         cout << "\n\nContinuing...\n\n";
         determineInstruction(currState);
      }
      else
         cout << "\n\nWaiting...\n\n";
   }
}

int main(int argc, char **argv)
{
   vector<string> args(argv, argv + argc);
   string filename = (args.size() > 1) ? args[1] : "../c8games/PONG";
   int frequency = atoi(((args.size() > 2) ? args[2] : "300").c_str());
   runRom(filename, frequency);
   
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
