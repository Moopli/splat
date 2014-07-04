#include <array>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

struct CHIP8state
{
   CHIP8state(string fn = "");
   array<unsigned char, 16> V; //V registers - 16
   short I; //I register
   short PC; //starts at 512
   int delayTimer;
   int soundTimer;
   array<unsigned char, 4096> RAM; //4096
   stack<short> theStack; //CHIP-8 supports
   //up to 16 levels of subroutine-calling
   array<bool, 16> keys; //16
   array<array<bool, 32>, 64> display;
   string filename;
};
