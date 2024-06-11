#include "../includes/iobase.hpp"
#include <iostream>

namespace TerreateIO {
namespace IOBase {
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
/* Reader::Reader() { */
/*   mFile.filedata = nullptr; */
/*   mFile.cursor = 0; */
/*   mFile.size = 0; */
/* } */

/* Reader::~Reader() { */
/*   if (mFile.filedata != nullptr) { */
/*     delete[] mFile.filedata; */
/*   } */
/* } */

/* void Reader::Open(Str const &path) { */
/*   mFile.path = path; */
/*   InputStream file(mFile.path, std::ios::binary); */
/*   if (!file.is_open()) { */
/*     throw std::runtime_error("Failed to open file: " + mFile.path); */
/*   } */
/*   file.seekg(0, std::ios::beg); */
/*   auto begin = file.tellg(); */
/*   file.seekg(0, std::ios::end); */
/*   mFile.size = static_cast<Size>(file.tellg() - begin); */
/*   file.seekg(0, std::ios::beg); */
/*   mFile.filedata = new Byte[mFile.size]; */
/*   file.read(reinterpret_cast<char *>(mFile.filedata), mFile.size); */
/*   file.close(); */
/* } */

/* Size Reader::Find(Char const &chr) const { */
/*   for (Size i = mFile.cursor; i < mFile.size; ++i) { */
/*     if (mFile.filedata[i] == chr) { */
/*       return i; */
/*     } */
/*   } */
/*   return mFile.eof; */
/* } */

/* Size Reader::Find(Char const *pattern, Size const &size) const { */
/*   for (Size i = mFile.cursor; i < mFile.size; ++i) { */
/*     if (mFile.filedata[i] == pattern[0]) { */
/*       bool found = true; */
/*       for (Size j = 1; j < size; ++j) { */
/*         if (mFile.filedata[i + j] != pattern[j]) { */
/*           found = false; */
/*           break; */
/*         } */
/*       } */
/*       if (found) { */
/*         return i; */
/*       } */
/*     } */
/*   } */
/*   return mFile.eof; */
/* } */

/* void Reader::Read(Byte *buffer, Size const &size) { */
/*   if (mFile.cursor + size > mFile.size) { */
/*     throw std::runtime_error("Read out of bounds"); */
/*   } */
/*   std::memcpy(buffer, mFile.filedata + mFile.cursor, size); */
/*   mFile.cursor += size; */
/* } */

/* Size Reader::ReadUntil(Char const &chr, Byte *buffer, Size const &maxSize) {
 */
/*   Size i = mFile.cursor; */
/*   for (; i < mFile.size; ++i) { */
/*     if (mFile.filedata[i] == chr) { */
/*       break; */
/*     } */
/*   } */
/*   Size size = i - mFile.cursor; */
/*   if (size > maxSize) { */
/*     size = maxSize; */
/*   } */
/*   std::memcpy(buffer, mFile.filedata + mFile.cursor, size); */
/*   mFile.cursor += size; */
/*   return size; */
/* } */

/* Size Reader::ReadUntil(Str const &pattern, Byte *buffer, Size const &maxSize)
 * { */
/*   Size i = mFile.cursor; */
/*   for (; i < mFile.size; ++i) { */
/*     if (mFile.filedata[i] == pattern[0]) { */
/*       bool found = true; */
/*       for (Size j = 1; j < pattern.size(); ++j) { */
/*         if (mFile.filedata[i + j] != pattern[j]) { */
/*           found = false; */
/*           break; */
/*         } */
/*       } */
/*       if (found) { */
/*         break; */
/*       } */
/*     } */
/*   } */
/*   Size size = i - mFile.cursor; */
/*   if (size > maxSize) { */
/*     size = maxSize; */
/*   } */
/*   std::memcpy(buffer, mFile.filedata + mFile.cursor, size); */
/*   mFile.cursor += size; */
/*   return size; */
/* } */

/* void Reader::IgnoreUntil(Char const &chr) { */
/*   for (Size i = mFile.cursor; i < mFile.size; ++i) { */
/*     if (mFile.filedata[i] == chr) { */
/*       mFile.cursor = i; */
/*       return; */
/*     } */
/*   } */
/* } */

/* void Reader::IgnoreUntil(Str const &pattern) { */
/*   for (Size i = mFile.cursor; i < mFile.size; ++i) { */
/*     if (mFile.filedata[i] == pattern[0]) { */
/*       bool found = true; */
/*       for (Size j = 1; j < pattern.size(); ++j) { */
/*         if (mFile.filedata[i + j] != pattern[j]) { */
/*           found = false; */
/*           break; */
/*         } */
/*       } */
/*       if (found) { */
/*         mFile.cursor = i; */
/*         return; */
/*       } */
/*     } */
/*   } */
/* } */

/* void Writer::Dump(Str const &path) { */
/*   OutputStream file(path, std::ios::binary); */
/*   if (!file.is_open()) { */
/*     throw std::runtime_error("Failed to open file: " + path); */
/*   } */
/*   file.write(mStream.str().c_str(), mStream.str().size()); */
/*   file.close(); */
/* } */
} // namespace IOBase
} // namespace TerreateIO
