#include "../includes/TerreateIO.hpp"

#include <iostream>

using namespace TerreateIO;
using namespace TerreateIO::Defines;

int main() {
  GLTF::GLTFParser parser("tests/resources/Cube/Cube.gltf");
  std::cout << parser.Parse() << std::endl;

  std::cout << parser.GetGLTFInfo() << std::endl;
  return 0;
}
