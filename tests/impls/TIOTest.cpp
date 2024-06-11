#include "../../includes/iobase.hpp"
#include <iostream>

using namespace TerreateIO;
using namespace TerreateIO::Defines;

int main() {
  /* IOBase::Writer writer; */
  /* writer << (Uint8)100 << (Uint16)10000 << (Uint32)1000000000 */
  /*        << (Uint64)1000000000000000000; */
  /* writer.Dump("resources/test.bin"); */

  IOBase::Reader reader;
  reader.Open("resources/test.bin");
  Uint8 u8;
  Uint16 u16;
  Uint32 u32;
  Uint64 u64;
  reader >> u8 >> u16 >> u32 >> u64;
  std::cout << (Uint64)u8 << " " << (Uint64)u16 << " " << (Uint64)u32 << " "
            << u64 << std::endl;
  return 0;
}
