#include "../includes/parser.hpp"
#include "../includes/exceptions.hpp"

namespace TerreateIO::Parser {
using namespace TerreateIO::Defines;

Buffer::ReadBuffer ParserBase::LoadFile(Str const &path) {
  InputFileStream file(path);
  if (!file.is_open()) {
    throw Exception::ParserException("Failed to open file: " + path);
  }

  Stream tempBuffer;
  tempBuffer << file.rdbuf();
  return Buffer::ReadBuffer(tempBuffer.str());
}

} // namespace TerreateIO::Parser
