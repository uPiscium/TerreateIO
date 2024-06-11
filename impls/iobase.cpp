#include "../includes/iobase.hpp"
#include <iostream>

namespace TerreateIO::IOBase {
using namespace TerreateIO::Defines;

Size Reader::Find(Char const &chr) const {
  for (Size i = mCursor; i < mSize; ++i) {
    if (mBuffer[i] == chr) {
      return i;
    }
  }
  return mSize + 1;
}

void Reader::Open(Str const &path) {
  mPath = path;
  InputStream file(mPath, std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file: " + mPath);
  }

  auto begin = file.tellg();
  file.seekg(0, std::ios::end);
  auto end = file.tellg();
  mSize = static_cast<Size>(end - begin);
  mEOF = mSize + 1;

  mBuffer = new Byte[mSize];
  file.clear();
  file.seekg(0, std::ios::beg);
  file.read(reinterpret_cast<char *>(mBuffer), mSize);
}

void Reader::Fetch(Byte *buffer, Size const &size) const {
  if (mCursor + size > mSize) {
    throw std::runtime_error("Fetch out of bounds");
  }
  std::memcpy(buffer, mBuffer + mCursor, size);
}

void Reader::Read(Byte *buffer, Size const &size) {
  this->Fetch(buffer, size);
  mCursor += size;
}

void Writer::Dump(Str const &path) {
  OutputStream file;
  if (path == "") {
    file.open(mPath, std::ios::binary);
  } else {
    file.open(path, std::ios::binary);
  }

  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file: " + path);
  }
  file.write(mStream.str().c_str(), mStream.str().size());
  file.close();
}
} // namespace TerreateIO::IOBase
