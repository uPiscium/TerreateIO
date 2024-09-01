#include "../includes/TerreateIO.hpp"

#include <iostream>

using namespace TerreateIO;

int main() {
  JSON::JSONParser parser("tests/resources/test.json");
  bool s = parser.Parse();
  JSON::JSON json = parser.GetRoot();
  std::cout << json << std::endl;
  return 0;
}
