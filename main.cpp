#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "opcodeProcessing.h"

using namespace std;

// TODO: Don't hardcode the ROM path!

int main(int argc, char ** argv)
{
   ifstream rom("../c8games/PONG", fstream::in);

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
   
   // stuff
   return 0;
}
