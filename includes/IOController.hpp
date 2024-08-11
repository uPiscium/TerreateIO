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
  ;
};

class Writer {
  ;
};
} // namespace TerreateIO::IOController

#endif // __TERREATEIO_IOCONTROLLER_HPP__
