#include "../includes/io.hpp"
#include <iostream>

using namespace TerreateIO::IO;

int main() {
  StringBuffer buffer("Hello, World!");
  std::cout << buffer.GetSize() << std::endl;
  return 0;
}
