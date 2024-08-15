#ifndef __TERREATEIO_EXCEPTIONS_HPP__
#define __TERREATEIO_EXCEPTIONS_HPP__

#include <exception>

#include "defines.hpp"

namespace TerreateIO::Exception {
using namespace TerreateIO::Defines;

class TerreateIOException : std::exception {
private:
  Str mMessage;

public:
  TerreateIOException(Str const &msg) : mMessage(msg) {}
  char const *what() const noexcept { return mMessage.c_str(); }
};

class FileIOError : public TerreateIOException {
public:
  FileIOError(Str const &msg) : TerreateIOException(msg) {}
};

class StringBufferError : public TerreateIOException {
public:
  StringBufferError(Str const &msg) : TerreateIOException(msg) {}
};

class ParserError : public TerreateIOException {
public:
  ParserError(Str const &msg) : TerreateIOException(msg) {}
};

class JsonError : public ParserError {
public:
  JsonError(Str const &msg) : ParserError(msg) {}
};

} // namespace TerreateIO::Exception

#endif // __TERREATEIO_EXCEPTIONS_HPP__
