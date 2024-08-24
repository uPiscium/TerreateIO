#include "../includes/TeerreateIO.hpp"

#include <iostream>

using namespace TerreateIO;

int main() {
  Buffer::ReadBuffer buffer =
      Parser::ParserBase::LoadFile("tests/resources/testFile.txt");
  std::cout << buffer.GetSize() << std::endl;
  std::cout << buffer.Read(buffer.GetSize()) << std::endl;
}
