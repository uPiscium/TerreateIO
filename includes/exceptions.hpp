#ifndef __TERRATEIO_EXCEPTIONS_HPP__
#define __TERRATEIO_EXCEPTIONS_HPP__

#include <exception>

#include "defines.hpp"

namespace TerreateIO::Exception {
using namespace TerreateIO::Defines;

class TerreateIOException : public std::exception {
private:
  Str mMessage;

public:
  TerreateIOException(Str const &message) : mMessage(message) {}

  virtual const char *what() const noexcept override {
    return mMessage.c_str();
  }
};

class BufferException : public TerreateIOException {
public:
  BufferException(Str const &message) : TerreateIOException(message) {}
};

class ParserException : public TerreateIOException {
public:
  ParserException(Str const &message) : TerreateIOException(message) {}
};

class JsonException : public TerreateIOException {
public:
  JsonException(Str const &message) : TerreateIOException(message) {}
};

} // namespace TerreateIO::Exception

#endif // __TERRATEIO_EXCEPTIONS_HPP__
