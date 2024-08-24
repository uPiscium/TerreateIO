#ifndef __TERREATEIO_PARSER_HPP__
#define __TERREATEIO_PARSER_HPP__

#include "buffer.hpp"
#include "defines.hpp"

namespace TerreateIO::Parser {
using namespace TerreateIO::Defines;

class ParserBase : public TerreateObjectBase {
public:
  ParserBase() {}
  virtual ~ParserBase() override {}

  virtual void Parse(Buffer::ReadBuffer &buffer) = 0;

public:
  static Buffer::ReadBuffer LoadFile(Str const &path);
};
} // namespace TerreateIO::Parser

#endif // __TERREATEIO_PARSER_HPP__
