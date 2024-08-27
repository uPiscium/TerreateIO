#include "../includes/TerreateIO.hpp"

#include <iostream>

using namespace TerreateIO;

int main() {
  Json::JsonParser parser("tests/resources/test.json");
  bool s = parser.Parse();
  Json::Json json = parser.GetRoot();
  std::cout << json << std::endl;
  return 0;
}
