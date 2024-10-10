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

class ContainerException : public TerreateIOException {
public:
  ContainerException(Str const &message) : TerreateIOException(message) {}
};

class BufferException : public TerreateIOException {
public:
  BufferException(Str const &message) : TerreateIOException(message) {}
};

class ParserException : public TerreateIOException {
public:
  ParserException(Str const &message) : TerreateIOException(message) {}
};

class JSONException : public TerreateIOException {
public:
  JSONException(Str const &message) : TerreateIOException(message) {}
};

class GLTFException : public TerreateIOException {
public:
  GLTFException(Str const &message) : TerreateIOException(message) {}
};

class ComposerException : public TerreateIOException {
public:
  ComposerException(const char *message) : TerreateIOException(message) {}
  ComposerException(const std::string &message)
      : TerreateIOException(message) {}
};

} // namespace TerreateIO::Exception

#endif // __TERRATEIO_EXCEPTIONS_HPP__
