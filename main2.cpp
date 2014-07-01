#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

using namespace std;

using Byte = unsigned char;
const int RAM_SIZE = 0x1000;
const int PC = 0x200;

Byte RAM[RAM_SIZE];

//Represents an opcode.
class Opcode
{
public:
   Opcode(uint16_t opcode) : m_opcode{opcode}
   {
   }

   uint16_t get() const
   {
      return m_opcode;
   }

private:
   uint16_t m_opcode;
};

void readRom(const string &filename)
{
   ifstream fin{filename, ios::binary};
   istream_iterator<Byte> first(fin);
   copy_n(first, RAM_SIZE - PC, RAM + PC);

   if (!fin.eof())
   {
      throw runtime_error("ROM is too big.");
   }
}

void dumpWord(Byte *p)
{
   for (auto i = 0; i < 2; ++i)
   {
      cout << hex << uppercase << setfill('0') << setw(2) << static_cast<unsigned>(p[i]);
   }
}

void dumpRAM()
{
   for (auto i = 0; i < RAM_SIZE; i += 2)
   {
      dumpWord(RAM + i);
      cout << '\n';
   }
}

int main()
{
   try
   {
      readRom("../c8games/PONG");
      dumpRAM();
   }

   catch (const exception &e)
   {
      cerr << e.what() << '\n';
      return EXIT_FAILURE;
   }
}