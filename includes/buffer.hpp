#ifndef __TERREATEIO_BUFFER_HPP__
#define __TERREATEIO_BUFFER_HPP__

#include <cstring>

#include "defines.hpp"
#include "exceptions.hpp"

namespace TerreateIO::Core {
using namespace TerreateIO::Defines;

constexpr Byte const EOB = -1;

class ReadBuffer : public TerreateObjectBase {
private:
  Byte *mBuffer = nullptr;
  Byte *mCursor = nullptr;
  Size mSize = 0u;

public:
  ReadBuffer() = default;
  ReadBuffer(Size const &size)
      : mBuffer(new Byte[size]), mCursor(mBuffer), mSize(size) {}
  ReadBuffer(Str const &buffer)
      : mBuffer(new Byte[buffer.size()]), mCursor(mBuffer),
        mSize(buffer.size()) {
    std::memcpy(mBuffer, buffer.data(), buffer.size());
  }
  ReadBuffer(Byte *buffer, Size const &size)
      : mBuffer(buffer), mCursor(mBuffer), mSize(size) {}
  ReadBuffer(ReadBuffer const &buffer)
      : mBuffer(new Byte[buffer.mSize]), mCursor(mBuffer), mSize(buffer.mSize) {
    std::memcpy(mBuffer, buffer.mBuffer, buffer.mSize);
  }
  ~ReadBuffer() override;

  Byte *GetBuffer() { return mBuffer; }
  Byte const *GetBuffer() const { return mBuffer; }
  Byte *GetCursor() { return mCursor; }
  Byte const *GetCursor() const { return mCursor; }
  Size const &GetSize() const { return mSize; }

  Str Fetch(Size const &size = 1u);
  Str Read(Size const &size = 1u);
  template <typename T> T Read() {
    T data;
    if (mCursor + sizeof(T) > mBuffer + mSize) {
      throw Exception::BufferException("Buffer out of bounds");
    }
    std::memcpy(&data, mCursor, sizeof(T));
    mCursor += sizeof(T);
    return data;
  }
  Byte Peek() { return this->Fetch()[0]; }
  void Skip(Size const &size = 1u);
  void SkipWhitespace();

  ReadBuffer &operator=(ReadBuffer const &buffer);
};

class WriteBuffer : public TerreateObjectBase {
private:
  Stream mStream;

public:
  WriteBuffer() = default;
  WriteBuffer(WriteBuffer const &buffer) : mStream(buffer.mStream.str()) {}
  ~WriteBuffer() override = default;

  void Write(Str const &data) { mStream << data; }
  void Write(Byte const *data, Size const &size) {
    mStream.write((const char *)data, size);
  }
  template <typename T> void Write(T const &data) {
    this->Write((Byte const *)&data, sizeof(T));
  }

  Str Dump() const { return mStream.str(); }

  WriteBuffer &operator=(WriteBuffer const &buffer);
};

} // namespace TerreateIO::Core

#endif // __TERREATEIO_BUFFER_HPP__
