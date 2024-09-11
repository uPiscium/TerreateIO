#include "../includes/TerreateIO.hpp"

#include <iostream>

using namespace TerreateIO;
using namespace TerreateIO::Defines;

int main() {
  /* GLTF::GLTFParser parser("tests/resources/Cube/Cube.gltf"); */
  /* std::cout << parser.Parse() << std::endl; */

  Str raw = "Hello, World!";
  Str base64 = Core::BASE64::Encode(raw);
  std::cout << base64 << std::endl;
  Str decoded = Core::BASE64::Decode(base64);
  std::cout << decoded << std::endl;
  return 0;
}
