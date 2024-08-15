#ifndef __TERREATEIO_PARSER_HPP__
#define __TERREATEIO_PARSER_HPP__

#include "IOController.hpp"
#include "defines.hpp"
#include "stringBuffer.hpp"

namespace TerreateIO::Parser {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Buffer;
using namespace TerreateIO::IOController;

class ParserBase : public TerreateObjectBase {
protected:
  Bool mParsed = false;
  StringBuffer mBuffer;
  Vec<Vec<Uint>> mFaceIndices;
  Vec<Vec<Uint>> mVertexIndices;
  Map<Str, Vec<Vec<Float>>> mVertexComponents;

public:
  ParserBase(Str const &filepath) : mBuffer(FileIO::ReadFile(filepath)) {}
  virtual ~ParserBase() {}

  virtual Vec<Vec<Uint>> GetFaceIndices() const { return mFaceIndices; }
  virtual Vec<Vec<Uint>> GetVertexIndices() const { return mVertexIndices; }
  virtual Map<Str, Vec<Vec<Float>>> GetVertexComponents() const {
    return mVertexComponents;
  }

  virtual Bool IsParsed() const { return mParsed; }

  virtual void Parse() = 0;

public:
  static Str Escape(Byte const &chr);
  static Str Escape(Str const &str);
};
} // namespace TerreateIO::Parser

#endif // __TERREATEIO_PARSER_HPP__
