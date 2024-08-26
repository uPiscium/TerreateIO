#ifndef __TERREATEIO_PARSER_HPP__
#define __TERREATEIO_PARSER_HPP__

#include "buffer.hpp"
#include "defines.hpp"

namespace TerreateIO::Parser {
using namespace TerreateIO::Defines;

class ParserBase : public TerreateObjectBase {
protected:
  Str mFilePath;

public:
  ParserBase() {}
  ParserBase(Str const &path) : mFilePath(path) {}
  virtual ~ParserBase() override {}

  virtual Bool Parse(Buffer::ReadBuffer &buffer) = 0;
  virtual Bool Parse() = 0;

public:
  static Buffer::ReadBuffer LoadFile(Str const &path);
  static Str Escape(Byte const &chr);
  static Str Unescape(Byte const &chr);
};
} // namespace TerreateIO::Parser

#endif // __TERREATEIO_PARSER_HPP__
