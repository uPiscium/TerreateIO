#include "../includes/buffer.hpp"

#include <iostream>

using namespace TerreateIO;

int main() {
  Buffer::WriteBuffer wb;
  wb.Write((unsigned)1000);
  Buffer::ReadBuffer rb(wb.Dump());
  std::cout << rb.Read<int>() << std::endl;
}
