#include "../../includes/iobase.hpp"
#include <iostream>

using namespace TerreateIO;

int main() {
  IOBase::Reader reader;
  reader.Open("resources/testOutput.bin");
  int a, b, c, d;
  reader >> a >> b >> c >> d;
  std::cout << a << " " << b << " " << c << " " << d << std::endl;
  return 0;
}
