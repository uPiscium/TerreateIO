#include "../includes/TeerreateIO.hpp"

#include <iostream>

using namespace TerreateIO;

int main() {
  Buffer::ReadBuffer buffer =
      Parser::ParserBase::LoadFile("tests/resources/testFile.txt");
  Buffer::WriteBuffer writeBuffer;
  writeBuffer.Write(buffer.Read(buffer.GetSize()));
  Composer::ComposerBase::SaveFile("tests/resources/testFile2.txt",
                                   writeBuffer);
  return 0;
}
