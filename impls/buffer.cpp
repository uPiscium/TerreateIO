#include "../includes/buffer.hpp"

namespace TerreateIO::Buffer {
using namespace TerreateIO::Defines;

ReadBuffer::~ReadBuffer() {
  if (mBuffer != nullptr) {
    delete[] mBuffer;
  }
}

Str ReadBuffer::Fetch(Size const &size) {
  Str result;
  if (mCursor + size > mBuffer + mSize) {
    Str temp;
    temp += EOB;
    return temp;
  } else {
    result = Str(mCursor, mCursor + size);
  }
  return result;
}

Str ReadBuffer::Read(Size const &size) {
  Str result;
  if (mCursor + size > mBuffer + mSize) {
    Str temp;
    temp += EOB;
    return temp;
  } else {
    result = Str(mCursor, mCursor + size);
    mCursor += size;
  }
  return result;
}

void ReadBuffer::Skip(Size const &size) {
  if (mCursor + size > mBuffer + mSize) {
    throw Exception::BufferException("Buffer out of bounds");
  } else {
    mCursor += size;
  }
}

void ReadBuffer::SkipWhitespace() {
  while (mCursor < mBuffer + mSize &&
         (*mCursor == ' ' || *mCursor == '\t' || *mCursor == '\n' ||
          *mCursor == '\r' || *mCursor == '\f' || *mCursor == '\v')) {
    ++mCursor;
  }
}

ReadBuffer &ReadBuffer::operator=(ReadBuffer const &buffer) {
  if (this != &buffer) {
    if (mBuffer != nullptr) {
      delete[] mBuffer;
    }
    mBuffer = new Byte[buffer.mSize];
    mCursor = mBuffer;
    mSize = buffer.mSize;
    std::memcpy(mBuffer, buffer.mBuffer, buffer.mSize);
  }
  return *this;
}

WriteBuffer &WriteBuffer::operator=(WriteBuffer const &buffer) {
  if (this != &buffer) {
    mStream.str(buffer.mStream.str());
  }
  return *this;
}
} // namespace TerreateIO::Buffer
