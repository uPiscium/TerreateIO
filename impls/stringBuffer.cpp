#include "../includes/stringBuffer.hpp"
#include <cstring>

namespace TerreateIO::Buffer {
using namespace TerreateIO::Defines;

StringBuffer::StringBuffer(Size const &capacity) {
  this->capacity = capacity;
  this->buffer = new Byte[capacity];
  this->top = &this->buffer[0];
  this->bottom = &this->buffer[this->capacity - 1];
  this->cursor = this->top;
}

StringBuffer::StringBuffer(StringBuffer const &other) {
  this->capacity = other.capacity;
  this->buffer = new Byte[capacity];
  std::memcpy(this->buffer, other.buffer, this->capacity);
  this->top = other.top;
  this->bottom = other.bottom;
  this->cursor = other.cursor;
}

StringBuffer::StringBuffer(StringBuffer &&other) {
  this->capacity = other.capacity;
  this->buffer = other.buffer;
  this->top = other.top;
  this->bottom = other.bottom;
  this->cursor = other.cursor;
}

StringBuffer::StringBuffer(Str const &str) {
  this->capacity = str.size() + 1;
  this->buffer = new Byte[this->capacity];
  this->buffer[this->capacity - 1] = '\0';
  this->top = &this->buffer[0];
  this->bottom = &this->buffer[this->capacity - 1];
  this->cursor = this->top;
}

StringBuffer::StringBuffer(Byte const *data, Size const &size) {
  this->capacity = size;
  this->buffer = new Byte[this->capacity];
  this->top = &this->buffer[0];
  this->bottom = &this->buffer[this->capacity - 1];
  this->cursor = this->top;
}

StringBuffer::StringBuffer(Byte const *begin, Byte const *end) {
  this->capacity = (Size)(end - begin);
  this->buffer = new Byte[this->capacity];
  this->top = &this->buffer[0];
  this->bottom = &this->buffer[this->capacity - 1];
  this->cursor = this->top;
}

StringBuffer::~StringBuffer() {
  if (this->buffer != nullptr) {
    delete[] this->buffer;
  }
}

void StringBuffer::LoadBuffer(Byte const *buffer, Size const &size) {
  if (size > this->capacity) {
    delete[] this->buffer;
    this->capacity = size;
    this->buffer = new Byte[this->capacity];
    this->top = &this->buffer[0];
    this->bottom = &this->buffer[this->capacity - 1];
    this->cursor = this->top;
  }
  std::memcpy(this->buffer, buffer, size);
}

StringBuffer StringBuffer::Copy() {
  StringBuffer copy(this->capacity);
  std::memcpy(copy.buffer, this->buffer, this->capacity);
  copy.top = this->top;
  copy.bottom = this->bottom;
  copy.cursor = this->cursor;
  return copy;
}

StringBufferRef StringBuffer::Ref() {
  StringBufferRef ref(*this);
  ref.buffer = this->buffer;
  ref.top = this->top;
  ref.bottom = this->bottom;
  ref.cursor = this->cursor;
  ref.capacity = this->capacity;
  return ref;
}

StringBuffer &StringBuffer::operator=(StringBuffer const &other) {
  if (this->buffer != nullptr) {
    delete[] this->buffer;
  }
  this->capacity = other.capacity;
  this->buffer = new Byte[this->capacity];
  std::memcpy(this->buffer, other.buffer, this->capacity);
  this->top = other.top;
  this->bottom = other.bottom;
  this->cursor = other.cursor;
  return *this;
}

StringBuffer &StringBuffer::operator=(StringBuffer &&other) {
  if (this->buffer != nullptr) {
    delete[] this->buffer;
  }
  this->capacity = other.capacity;
  this->buffer = other.buffer;
  this->top = other.top;
  this->bottom = other.bottom;
  this->cursor = other.cursor;
  return *this;
}

StringBuffer &StringBuffer::operator=(Str const &str) {
  if (this->buffer != nullptr) {
    delete[] this->buffer;
  }
  this->capacity = str.size() + 1;
  this->buffer = new Byte[this->capacity];
  this->buffer[this->capacity - 1] = '\0';
  this->top = &this->buffer[0];
  this->bottom = &this->buffer[this->capacity - 1];
  this->cursor = this->top;
  return *this;
}

} // namespace TerreateIO::Buffer
