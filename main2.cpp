//TODO: Figure out how to best store the opcodes from the ROM
//within some data structure (stringstream, string, array,
//something else, etc.).

#include <array>     //array
#include <cstdint>   //uint16_t
#include <cstdlib>   //EXIT_FAILURE
#include <fstream>   //ifstream
#include <iomanip>   //setw, setfill, hex, uppercase
#include <iostream>  //cout, cerr
#include <iterator>  //istream_iterator
#include <sstream>   //ostringstream
#include <stdexcept> //runtime_error
#include <string>    //string
#include <vector>    //vector

//read this if you haven't and rethink this decision
//stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-a-bad-practice-in-c
using namespace std;

const int OPCODE_LENGTH = 4;

//Represents an opcode.
class Opcode
{
   //read the opcode
   friend istream &operator>>(istream &is, Opcode &opcode);

public:
   //initialize to 0
   Opcode() : m_opcode{string(OPCODE_LENGTH, '?')}
   {
   }

   //get value
   uint16_t code() const
   {
      size_t pos;
      auto ret = stoi(m_opcode, &pos, 16);

      if (pos != m_opcode.size())
      {
         throw runtime_error("Failed to convert opcode " + m_opcode + " to uint16_t.");
      }

      return ret;
   }

   //get hex string representation
   string toString() const
   {
      return m_opcode;
   }

private:
   string m_opcode;
};

//Extracts an opcode from an input stream.
istream &operator>>(istream &is, Opcode &opcode)
{
   //2 characters is 4 nibbles
   array<char, OPCODE_LENGTH / 2> buffer;
   is.read(buffer.data(), OPCODE_LENGTH / 2);

   if (is.gcount() != OPCODE_LENGTH / 2)
   {
      is.setstate(ios::failbit);
   }

   ostringstream oss;
   for (auto c : buffer)
   {
      auto uc = static_cast<unsigned char>(c); //otherwise negative values suck
      oss << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(uc);
   }

#if 0
    if (!opcode.isValid()) //or something
    {
        is.setstate(ios::failbit);
    }
#endif

   opcode.m_opcode = oss.str();
   return is;
}

//Inserts an opcode to an output stream.
ostream &operator<<(ostream &os, Opcode opcode)
{
   return os << opcode.toString();
}

//reads a ROM file as a list of opcodes
vector<Opcode> readRom(string filename)
{
   ifstream fin{filename, ios::binary};

   //read opcodes into vector until the stream fails
   istream_iterator<Opcode> first{fin}, last;
   vector<Opcode> ret{first, last};

   //if we haven't hit the end of the stream, there's a problem
   if (!fin.eof())
   {
      throw runtime_error("Failed to read ROM.");
   }

   return ret;
}

int main()
{
   try
   {
      //read PONG and output opcodes
      auto opcodes = readRom("../c8games/PONG");
      for (auto oc : opcodes)
      {
         cout << oc << '\n';
      }
   }

   catch (const exception &e)
   {
      cerr << e.what() << '\n';
      return EXIT_FAILURE;
   }
}