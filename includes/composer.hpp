#ifndef __TERREATEIO_COMPOSER_HPP__
#define __TERREATEIO_COMPOSER_HPP__

#include "buffer.hpp"
#include "defines.hpp"

namespace TerreateIO::Core {
using namespace TerreateIO::Defines;

class ComposerBase : public TerreateObjectBase {
protected:
  Str mFilePath;
  Buffer::WriteBuffer mBuffer;

public:
  ComposerBase() {}
  ComposerBase(Str const &path) : mFilePath(path) {}
  virtual ~ComposerBase() override {}

  Buffer::WriteBuffer const &GetComposed() const { return mBuffer; }
  Buffer::WriteBuffer &GetComposed() { return mBuffer; }

  template <typename T> void Compose(T const &data) { mBuffer.Write(data); }

public:
  static void SaveFile(Str const &path, Buffer::WriteBuffer const &buffer);
};
} // namespace TerreateIO::Core

#endif // __TERREATEIO_COMPOSER_HPP__
