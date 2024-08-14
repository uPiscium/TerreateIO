#ifndef __TERREATEIO_IOCONTROLLER_HPP__
#define __TERREATEIO_IOCONTROLLER_HPP__

#include "defines.hpp"
#include "stringBuffer.hpp"

namespace TerreateIO::IOController {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Buffer;

class FileIO {
public:
  static StringBuffer ReadFile(Str const &filename);
  static void WriteFile(Str const &filename, StringBuffer const &buffer);
};

class Reader {
public:
  static Size Find(Str const &pattern, StringBuffer const &buffer);
  static Str Fetch(Size const &size, StringBuffer const &buffer);
  static Str Read(Size const &size, StringBuffer &buffer);
  static Str ReadUntil(Str const &pattern, StringBuffer &buffer);
  static void Rollback(Size const &size, StringBuffer &buffer);
  static void Skip(Size const &size, StringBuffer &buffer);
  static void SkipWhitespace(StringBuffer &buffer);
};

class Writer {
private:
  template <typename T> static void Write(T const &data, StringBuffer &buffer);
  static void Write(Str const &str, StringBuffer &buffer);
};
} // namespace TerreateIO::IOController

#endif // __TERREATEIO_IOCONTROLLER_HPP__
