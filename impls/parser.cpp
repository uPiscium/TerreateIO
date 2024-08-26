#include "../includes/parser.hpp"
#include "../includes/exceptions.hpp"

namespace TerreateIO::Core {
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

Str ParserBase::Escape(Byte const &chr) {
  switch (chr) {
  case '"':
    return "\\\"";
  case '\\':
    return "\\\\";
  case '\b':
    return "\\b";
  case '\f':
    return "\\f";
  case '\n':
    return "\\n";
  case '\r':
    return "\\r";
  case '\t':
    return "\\t";
  default:
    Str buf;
    buf += chr;
    return buf;
  }
}

Str ParserBase::Unescape(Byte const &chr) {
  Str buf;
  switch (chr) {
  case '"':
    buf += '\"';
    break;
  case '\\':
    buf += '\\';
    break;
  case 'b':
    buf += '\b';
    break;
  case 'f':
    buf += '\f';
    break;
  case 'n':
    buf += '\n';
    break;
  case 'r':
    buf += '\r';
    break;
  case 't':
    buf += '\t';
    break;
  default:
    buf += chr;
    break;
  }
  return buf;
}

} // namespace TerreateIO::Core
