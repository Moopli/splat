#include <iostream>
#include <iomanip>
#include <sstream>
#include <stack>
#include "opcodeProcessing.h"
#include <cassert>
#include <utility>

//move this somewhere useful later
//take any arguments and do nothing
template<typename... Args>
void swallow(Args &&...)
{
}

//and this
#ifdef NDEBUG
//do nothing if NDEBUG is defined
template<typename... Args>
void dbgprint(Args &&...)
{
}
#else
//see http: //coliru.stacked-crooked.com/a/9ecfb273081061f4 for a sample
//basically do cout << arg; for each arg, passing the result to swallow each time
//note that using std::endl won't work with this, but it's unimportant with '\n' anyway
template<typename... Args>
void dbgprint(Args &&... args)
{
   swallow((cout << forward<Args>(args))...);
}
#endif

//@param (short) opcode: the current opcode being processed
//@param (int *) RAM: a pointer to the RAM
//@param (short) PC: a reference to the current value of PC
//@param (stack<short>) theStack: a reference to a stack of the previous
//values of PC; this is necessary for returning from a subroutine
void determineInstruction(CHIP8state &currState)
{
   cout << hex;
   short opcode = (currState.RAM[currState.PC] << 8) | currState.RAM[currState.PC + 1];
   dbgprint("\nPROCESSING ", showbase, hex, opcode, '\n');
   unsigned char x;
   short constant;

   switch (opcode & 0xF000)
   {
      case 0x0000:
         if ((opcode & 0xFFF0) == 0x00E0)
         {
            //clear screen
            dbgprint("case 0x0000\n");
         }

         else if ((opcode & 0xFFFF) == 0x00EE)
         {
            //return from subroutine -- we'll need to keep track of the value
            //of PC before jumping to a subroutine
            dbgprint("case 0x00EE\n");
            // We assume the stack can always be popped, because if this is being
            // called, we should assume the program knows what it's doing.
            currState.PC = currState.theStack.top();
            currState.theStack.pop();
            dbgprint("Returned from subroutine!\n");
         }

         else
         {
            //invalid opcode
            dbgprint("INVALID!\n");
            currState.PC = 0; //stop loop
            return;
         }

         currState.PC += 2;
         break;
      case 0x1000:
         currState.PC = opcode - 0x1000;
         dbgprint("case 0x1000\n");
         cout << "PC was " << currState.PC << endl;
         currState.PC = opcode & 0x0FFF;
         cout << "PC is now " << currState.PC << endl;
         break;
      case 0x2000:
         currState.theStack.push(currState.PC);
         currState.PC = opcode - 0x2000;
         dbgprint("case 0x2000\n");
         dbgprint("Called subroutine!!\n");
         cout << "PC is now " << currState.PC << endl;
         break;
      case 0x3000:
         //skip next instruction if Vx equals a constant
         //if Vx == kk, PC += 4
         //else, PC += 2
         dbgprint("case 0x3000\n");
         if (currState.V[(opcode - 0x4000)/256] != (opcode & 0xFF))
         {
            currState.PC += 4;
            cout << "Jump 4\n";
         }
         else
         {
            currState.PC += 2;
            cout << "Jump 2\n";
         }
         break;
      case 0x4000:
         //skip next instruction if Vx doesn't equal a constant
         dbgprint("case 0x4000\n");
         if (currState.V[(opcode - 0x4000)/256] != (opcode & 0xFF))
         {
            currState.PC += 4;
            cout << "Jump 4\n";
         }
         else
         {
            currState.PC += 2;
            cout << "Jump 2\n";
         }
         break;
      case 0x5000:
         //skip next instruction if two registers are equal
         //if Vx == Vy, PC += 4
         //else, PC == 2
         dbgprint("case 0x5000\n");
         //if Vx == Vy, PC += 4
         if (currState.V[(opcode - 0x9000)/256] == currState.V[(opcode - 0x9000)/256])
         {
            currState.PC += 4;
            cout << "Jump 4\n";
         }
         else
         {
            currState.PC += 2;
            cout << "Jump 2\n";
         }
         break;
      case 0x6000:
         //set Vx to a constant
         x = (opcode - 0x6000) / 256;
         constant = opcode & 0x00FF;
         currState.V[(size_t)x] = constant;
         dbgprint("case 0x6000\n");
         std::cout << "V" << dec << (int)x << " set to " << \
         constant << " = " << dec << (int)constant << hex << std::endl;
         currState.PC += 2;
         break;
      case 0x7000:
         //add a constant to Vx, and store in Vx
         x = (opcode - 0x7000) / 256;
         constant = opcode & 0x00FF;
         currState.V[x] += constant;
         dbgprint("case 0x7000\n");
         std::cout << "V" << dec << (int)x << " set to " << dec << \
         constant << " so now equals " << (short)currState.V[x] << hex << std::endl;
         currState.PC += 2;
         break;
      case 0x8000:
         //requires more processing - maybe have another function to do this?
         process0x8000Codes(currState, opcode);
         dbgprint("case 0x8000\n");
         currState.PC += 2;
         break;
      case 0x9000:
         //skip next instruction if two registers are not equal
         dbgprint("case 0x9000\n");
         //if Vx != Vy, PC += 4
         if (currState.V[(opcode - 0x9000)/256] != currState.V[(opcode - 0x9000)/256])
         {
            currState.PC += 4;
            cout << "Jump 4\n";
         }
         else
         {
            currState.PC += 2;
            cout << "Jump 2\n";
         }
         break;
      case 0xA000:
         //set I register to a constant
         dbgprint("case 0xA000\n");
         currState.I = opcode & 0xFFF;
         cout << "I register set to " << dec << currState.I << hex << endl;
         currState.PC += 2;
         break;
      case 0xB000:
         //jump to location nnn + V0
         dbgprint("case 0xB000\n");
         cout << "PC was " << currState.PC << endl;
         currState.PC = (opcode & 0x0FFF) + currState.V[0];
         cout << "PC is now " << currState.PC << endl;
         break;
      case 0xC000:
         //set Vx to random byte & kk
         //use math class random function
         dbgprint("case 0xC000\n");
         currState.PC += 2;
         break;
      case 0xD000:
         //display sprite on screen
         dbgprint("case 0xD000\n");
         currState.PC += 2;
         break;
      case 0xE000:
         //skip next instruction if a specific key is pressed or not.
         //The key corresponds to the value of Vx.
         //Let's have another thread to check key presses, and
         //store a bool array, saying which key is being pressed
         //current. This will obviously need to be updated
         //frequently!
         dbgprint("0xE000\n");
         currState.PC += 2;
         break;
      case 0xF000:
         //requires more processing - maybe have another function to do this?
         process0xF000Codes(currState, opcode);
         dbgprint("case 0xF000\n");
         currState.PC += 2;
         break;
      default:
         //unknown opcode - do we assert(0) or do we keep going?
         dbgprint("unknown opcode!\n");
         currState.PC += 2;
         break;
   }
}

void process0x8000Codes(CHIP8state &currState, short opcode)
{
   assert((opcode & 0xF000) == 0x8000);
}

void process0xF000Codes(CHIP8state &currState, short opcode)
{
   assert((opcode & 0xF000) == 0xF000);
}
