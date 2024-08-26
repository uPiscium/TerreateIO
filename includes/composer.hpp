#ifndef __TERREATEIO_COMPOSER_HPP__
#define __TERREATEIO_COMPOSER_HPP__

#include "buffer.hpp"
#include "defines.hpp"

namespace TerreateIO::Composer {
using namespace TerreateIO::Defines;

class ComposerBase : public TerreateObjectBase {
protected:
  Buffer::WriteBuffer mBuffer;

public:
  ComposerBase() {}
  virtual ~ComposerBase() override {}

  Buffer::WriteBuffer const &GetComposed() const { return mBuffer; }
  Buffer::WriteBuffer &GetComposed() { return mBuffer; }

public:
  static void SaveFile(Str const &path, Buffer::WriteBuffer const &buffer);
};
} // namespace TerreateIO::Composer

#endif // __TERREATEIO_COMPOSER_HPP__
