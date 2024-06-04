#ifndef __TIO_IOBASE_HPP__
#define __TIO_IOBASE_HPP__
#include "defines.hpp"
#include <cstring>

namespace TerreateIO {
namespace IOBase {
using namespace TerreateIO::Defines;

struct File {
  Str path;
  Size cursor;
  Size size;
  Size eof;
  Byte *filedata;
};

class Reader {
private:
  File mFile;

public:
  Reader();
  ~Reader();

  Size const &GetFileSize() const { return mFile.size; }

  void Open(Str const &path);
  Size Find(Char const &chr) const;
  Size Find(Char const *pattern, Size const &size) const;
  Size Find(Str const &pattern) const {
    return Find(pattern.c_str(), pattern.size());
  }
  void Fetch(Byte *buffer, Size const &size) const {
    std::memcpy(buffer, mFile.filedata + mFile.cursor, size);
  }
  template <typename T> void Fetch(T *dst) const {
    Fetch(reinterpret_cast<Byte *>(dst), sizeof(T));
  }
  template <typename T> void Fetch(T *dst[], Size const &size) const {
    Fetch(reinterpret_cast<Byte *>(dst), sizeof(T) * size);
  }
  template <typename T> void Fetch(Vec<T> &dst, Size const &size) const {
    dst.resize(size);
    Fetch(dst.data(), sizeof(T) * size);
  }
  void Read(Byte *buffer, Size const &size);
  template <typename T> void Read(T *dst) {
    Read(reinterpret_cast<Byte *>(dst), sizeof(T));
  }
  template <typename T> void Read(T *dst[], Size const &size) {
    Read(reinterpret_cast<Byte *>(dst), sizeof(T) * size);
  }
  template <typename T> void Read(Vec<T> &dst, Size const &size) {
    dst.resize(size);
    Read(dst.data(), sizeof(T) * size);
  }
  Size ReadUntil(Char const &chr, Byte *buffer, Size const &maxSize);
  Size ReadUntil(Str const &pattern, Byte *buffer, Size const &maxSize);
  void Ignore(Size const &size) { mFile.cursor += size; }
  void IgnoreUntil(Char const &chr);
  void IgnoreUntil(Str const &pattern);

  template <typename T> Reader &operator>>(T &dst) {
    Read(&dst);
    return *this;
  }
};

class Writer {
private:
  StrStream mStream;

public:
  Writer() {}
  ~Writer() {}

  void Write(Byte const *buffer, Size const &size) {
    mStream.write(reinterpret_cast<Char const *>(buffer), size);
  }
  template <typename T> void Write(T const *src) {
    Write(reinterpret_cast<Byte const *>(src), sizeof(T));
  }
  template <typename T> void Write(T const *src[], Size const &size) {
    Write(reinterpret_cast<Byte const *>(src), sizeof(T) * size);
  }
  template <typename T> void Write(Vec<T> const &src, Size const &size) {
    Write(src.data(), sizeof(T) * size);
  }
  void Dump(Str const &path);

  template <typename T> Writer &operator<<(T const &src) {
    Write(&src);
    return *this;
  }
};
} // namespace IOBase
} // namespace TerreateIO

#endif // __TIO_IOBASE_HPP__
