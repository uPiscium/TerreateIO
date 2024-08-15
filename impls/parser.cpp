#include "../includes/parser.hpp"

namespace TerreateIO::Parser {
using namespace TerreateIO::Defines;

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

Str ParserBase::Escape(Str const &str) {
  Str escaped;
  for (Uint i = 0; i < str.size(); i++) {
    escaped += ParserBase::Escape(str[i]);
  }
  return escaped;
}
} // namespace TerreateIO::Parser
