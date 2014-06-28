#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// TODO: Figure out how to best store the opcodes from the ROM
//	 within some data structure (stringstream, string, array,
//	 something else, etc.).

int main(int argc, char ** argv)
{
   ifstream rom("../c8games/PONG", fstream::in);

   stringstream opcodes;
   // opcodes[i] requires being cast to an unsigned
   // char and then an int (not unsigned int!) being useable.
   // string opcodes = "";
   unsigned char a = 0;
   int count = 0;
   while (rom >> hex >> a) // When dealing with hex stuff, we need this intermediate hex stream object
   {
      cout << hex << (int)a << endl;
      opcodes << hex << (int)a;
      if (count % 2 == 1)
          opcodes << hex << endl;
      count++;
      
      // opcodes.push_back(a);
   }
   rom.close();
   cout << "String:\n" << opcodes << endl;
   
   // stuff
   return 0;
}
