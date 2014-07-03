#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

struct CHIP8state
{
   CHIP8state();
   CHIP8state(string fn);
   ~CHIP8state();
   short * V; // V registers - 16
   short I; // I register
   short PC; // starts at 512
   int delayTimer;
   int soundTimer;
   unsigned char * RAM; // 4096
   stack<short> theStack; // CHIP-8 supports
   // up to 16 levels of subroutine-calling
   bool * keys; // 16
   bool display[64][32];
   string filename;
};

