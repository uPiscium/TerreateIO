#include "../includes/TeerreateIO.hpp"

#include <iostream>

using namespace TerreateIO;

int main() {
  Parser::Json::JsonParser parser("tests/resources/test.json");
  bool s = parser.Parse();
  Parser::Json::Json json = parser.GetRoot();
  std::cout << json << std::endl;
  return 0;
}
