#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "opcodeProcessing.h"

using namespace std;

int main(int, char **)
{
   ifstream rom("../c8games/PONG", ios::binary);

   stringstream opcodes;
   // Each opcode is stored in four successive chars, followed by
   // a newline. E.g., "5F20\n"
   // No casting is necessary to access these, just use array
   // syntax. To deal with the issue of the fact that we're
   // taking the values from an int, if a value is less than
   // F+1 (i.e., 16), the opcode will be shorter. This is why
   // there is a placeholder "0" appended to the string if
   // the current int is too small.
   unsigned char a = 0;
   int count = 0;
   //  When dealing with hex stuff, we need this intermediate hex stream object
   // Syntax:
   // sstreamObject << hex << (int)currentVar;
   while (rom >> hex >> a)
   {
      if (a < 16)
         opcodes << "0"; // Placeholder for parsing
      opcodes << hex << (int)a;
      if (count % 2 == 1)
         opcodes << hex << endl;
      count++;
   }
   rom.close();
   // See what the data looks like yourself:
   cout << "String:\n" << opcodes.str() << endl;
   cout << "Or in loop:\n";
   for (int i = 0; i < (int)opcodes.str().size(); i++)
   {
      cout << opcodes.str()[i];
   }
   cout << "\n\nActually important stuff:\n";

   // This is a test
   CHIP8state currState("../c8games/PONG");
   int i = 0;
   ifstream rom2("../c8games/PONG", ios::binary);
   while (rom2 >> a)
   {
      currState.RAM[512 + i] = a;
      cout << "a = " << (short)a << endl;
      cout << "i = " << i << endl;
      i++;
   }
   rom2.close();
   while (currState.PC >= 512 && currState.PC < 4096)
   {
      determineInstruction(currState);
      cout << "currState.PC = " << currState.PC << endl;
   }
   // stuff
   return 0;
}
