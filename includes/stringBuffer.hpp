#ifndef __TERREATEIO_STRINGBUFFER_HPP__
#define __TERREATEIO_STRINGBUFFER_HPP__

#include <cstring>

#include "defines.hpp"

namespace TerreateIO::Buffer {
using namespace TerreateIO::Defines;

struct StringBufferRef;

struct StringBuffer {
  Byte *buffer = nullptr;
  Byte *cursor = nullptr;
  Byte *top = nullptr;
  Byte *bottom = nullptr;
  Size capacity = 0u;

  StringBuffer(Size const &capacity);
  StringBuffer(StringBuffer const &other);
  StringBuffer(StringBuffer &&other);
  StringBuffer(Str const &str);
  StringBuffer(Byte const *data, Size const &size);
  StringBuffer(Byte const *begin, Byte const *end);
  virtual ~StringBuffer();

  Size GetSize() const { return bottom - top; }
  Size const &GetCapacity() const { return capacity; }
  Byte *GetBuffer() { return buffer; }
  Byte const *GetBuffer() const { return buffer; }
  Byte *GetTop() { return top; }
  Byte const *GetTop() const { return top; }
  Byte *GetBottom() { return bottom; }
  Byte const *GetBottom() const { return bottom; }
  Byte *GetCursor() { return cursor; }
  Byte const *GetCursor() const { return cursor; }

  void SetTop(Byte *top) { this->top = top; }
  void SetBottom(Byte *bottom) { this->bottom = bottom; }
  void SetCursor(Byte *cursor) { this->cursor = cursor; }

  void LoadBuffer(Byte const *buffer, Size const &size);
  void ClearBuffer() { std::memset(buffer, 0, capacity); }
  void ResetCursor() { cursor = top; }
  StringBuffer Copy();
  StringBufferRef Ref();

  StringBuffer &operator=(StringBuffer const &other);
  StringBuffer &operator=(StringBuffer &&other);
  StringBuffer &operator=(Str const &str);
};

struct StringBufferRef : public StringBuffer {
  StringBufferRef(StringBuffer &buffer) : StringBuffer(buffer) {}
  ~StringBufferRef() override {}
};

} // namespace TerreateIO::Buffer

#endif // __TERREATEIO_STRINGBUFFER_HPP__
