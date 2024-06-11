#ifndef __TIO_IOBASE_HPP__
#define __TIO_IOBASE_HPP__
#include "defines.hpp"
#include <cstring>

namespace TerreateIO::IOBase {
using namespace TerreateIO::Defines;

class Reader {
private:
  Str mPath;
  Size mCursor;
  Size mSize;
  Size mEOF;
  Byte *mBuffer;

public:
  Reader() : mCursor(0), mSize(0), mEOF(1), mBuffer(nullptr) {}
  Reader(Str const &path) : mCursor(0), mSize(0), mEOF(1), mBuffer(nullptr) {
    this->Open(path);
  }
  Reader(Byte const *buffer, Size const &size)
      : mCursor(0), mSize(size), mBuffer(new Byte[size]) {
    std::memcpy(mBuffer, buffer, size);
  }

  Str const &GetPath() const { return mPath; }
  Size const &GetCursor() const { return mCursor; }
  Size const &GetFileSize() const { return mSize; }
  Size const &GetEOF() const { return mEOF; }
  Byte const *GetBuffer() const { return mBuffer; }

  void Open(Str const &path);

  Size Find(Char const &chr) const;
  Size Find(Char const *pattern, Size const &size) const;
  Size Find(Str const &pattern) const {
    return Find(pattern.c_str(), pattern.size());
  }

  void Fetch(Byte *buffer, Size const &size) const;
  template <typename T> void Fetch(T *dst) const {
    Fetch(reinterpret_cast<Byte *>(dst), sizeof(T));
  }
  template <typename T> void Fetch(T **dst, Size const &size) const {
    Fetch(reinterpret_cast<Byte *>(&dst[0][0]), sizeof(T) * size);
  }

  void Read(Byte *buffer, Size const &size);
  template <typename T> void Read(T *dst) {
    Read(reinterpret_cast<Byte *>(dst), sizeof(T));
  }
  template <typename T> void Read(T **dst, Size const &size) {
    Read(reinterpret_cast<Byte *>(&dst[0][0]), sizeof(T) * size);
  }

  void Ignore(Size const &size) { mCursor += size; }

  template <typename T> Reader &operator>>(T &dst) {
    Read(&dst);
    return *this;
  }
};

class Writer {
private:
  Str mPath;
  StrStream mStream;

public:
  Writer() {}
  Writer(Str const &path) : mPath(path) {}

  Str const &GetPath() const { return mPath; }
  StrStream const &GetStream() const { return mStream; }

  void Write(Byte const *buffer, Size const &size) {
    mStream.write(reinterpret_cast<Char const *>(buffer), size);
  }
  template <typename T> void Write(T const *src) {
    Write(reinterpret_cast<Byte const *>(src), sizeof(T));
  }
  template <typename T> void Write(T const **src, Size const &size) {
    Write(reinterpret_cast<Byte const *>(&src[0][0]), sizeof(T) * size);
  }

  void Dump(Str const &path = "");

  template <typename T> Writer &operator<<(T const &src) {
    Write(&src);
    return *this;
  }
};
} // namespace TerreateIO::IOBase

#endif // __TIO_IOBASE_HPP__
