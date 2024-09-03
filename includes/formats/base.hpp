#ifndef __TERREATEIO_BASE_HPP__
#define __TERREATEIO_BASE_HPP__

#include "../defines.hpp"
#include "buffer.hpp"

namespace TerreateIO::Core {
using namespace TerreateIO::Defines;

class ParserBase : public TerreateObjectBase {
protected:
  Str mFilePath;

public:
  ParserBase() {}
  ParserBase(Str const &path) : mFilePath(path) {}
  virtual ~ParserBase() override {}

  virtual Bool Parse(ReadBuffer &buffer) = 0;
  virtual Bool Parse() = 0;

public:
  static ReadBuffer LoadFile(Str const &path);
  static Str Escape(Byte const &chr);
  static Str Unescape(Byte const &chr);
};

class ComposerBase : public TerreateObjectBase {
protected:
  Str mFilePath;
  WriteBuffer mBuffer;

public:
  ComposerBase() {}
  ComposerBase(Str const &path) : mFilePath(path) {}
  virtual ~ComposerBase() override {}

  WriteBuffer const &GetComposed() const { return mBuffer; }
  WriteBuffer &GetComposed() { return mBuffer; }

  template <typename T> void Compose(T const &data) { mBuffer.Write(data); }

public:
  static void SaveFile(Str const &path, WriteBuffer const &buffer);
};
} // namespace TerreateIO::Core

#endif // __TERREATEIO_BASE_HPP__
