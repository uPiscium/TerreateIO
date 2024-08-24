#ifndef __TERRATEIO_EXCEPTIONS_HPP__
#define __TERRATEIO_EXCEPTIONS_HPP__

#include <exception>

#include "defines.hpp"

namespace TerreateIO::Exception {
class TerreateIOException : public std::exception {
private:
  std::string mMessage;

public:
  TerreateIOException(const char *message) : mMessage(message) {}
  TerreateIOException(const std::string &message) : mMessage(message) {}

  virtual const char *what() const noexcept override {
    return mMessage.c_str();
  }
};

class BufferException : public TerreateIOException {
public:
  BufferException(const char *message) : TerreateIOException(message) {}
  BufferException(const std::string &message) : TerreateIOException(message) {}
};

class ParserException : public TerreateIOException {
public:
  ParserException(const char *message) : TerreateIOException(message) {}
  ParserException(const std::string &message) : TerreateIOException(message) {}
};

} // namespace TerreateIO::Exception

#endif // __TERRATEIO_EXCEPTIONS_HPP__
