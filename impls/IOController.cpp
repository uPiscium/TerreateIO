#include "../includes/IOController.hpp"
#include "../includes/exceptions.hpp"

namespace TerreateIO::IOController {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Buffer;

StringBuffer FileIO::ReadFile(Str const &filename) {
  InputFileStream file;
  file.open(filename, std::ios::in | std::ios::binary);
  if (!file.is_open()) {
    throw Exception::FileIOError("File: " + filename + " not found.");
  }

  Stream buffer;
  buffer << file.rdbuf();
  file.close();
  return StringBuffer(buffer.str());
}

void FileIO::WriteFile(Str const &filename, StringBuffer const &buffer) {
  OutputFileStream file;
  file.open(filename, std::ios::out | std::ios::binary);
  if (!file.is_open()) {
    throw Exception::FileIOError("File: " + filename + " not found.");
  }

  file.write((char const *)buffer.GetTop(), buffer.GetSize());
  file.close();
}

Size Reader::Find(Str const &pattern, StringBuffer const &buffer) {
  Byte const *cursor = buffer.GetCursor();
  Size size = buffer.GetSize();
  Size patternSize = pattern.size();
  if (size < patternSize) {
    throw Exception::StringBufferError(
        "Buffer size is less than pattern size.");
  }

  for (Size i = 0; i < size; ++i) {
    if (*(cursor + i) == pattern[0]) {
      bool found = true;
      Byte const *current = buffer.GetCursor() + i;
      for (Size j = 1; j < patternSize; j++) {
        if (*(current + j) != pattern[j]) {
          found = false;
          break;
        }
      }

      if (found) {
        return i;
      }
    }
  }

  return size;
}

Str Reader::Fetch(Size const &size, StringBuffer const &buffer) {
  if (size > buffer.GetSize()) {
    throw Exception::StringBufferError(
        "Buffer size is less than requested size.");
  }

  return Str((char const *)buffer.GetTop(), size);
}

Str Reader::Read(Size const &size, StringBuffer &buffer) {
  if (size > buffer.GetSize()) {
    throw Exception::StringBufferError(
        "Buffer size is less than requested size.");
  }

  Str str((char const *)buffer.GetTop(), size);
  buffer.SetCursor(buffer.GetCursor() + size);
  return str;
}

Str Reader::ReadUntil(Str const &pattern, StringBuffer &buffer) {
  Size index = Find(pattern, buffer);
  if (index == buffer.GetSize()) {
    throw Exception::StringBufferError("Pattern not found.");
  }

  Str str((char const *)buffer.GetTop(), index);
  buffer.SetCursor(buffer.GetCursor() + index + pattern.size());
  return str;
}

void Reader::Rollback(Size const &size, StringBuffer &buffer) {
  if (size > buffer.GetSize()) {
    throw Exception::StringBufferError(
        "Buffer size is less than requested size.");
  }

  buffer.SetCursor(buffer.GetCursor() - size);
}

void Reader::Skip(Size const &size, StringBuffer &buffer) {
  if (size > buffer.GetSize()) {
    throw Exception::StringBufferError(
        "Buffer size is less than requested size.");
  }

  buffer.SetCursor(buffer.GetCursor() + size);
}

void Reader::SkipWhitespace(StringBuffer &buffer) {
  Byte *cursor = buffer.GetCursor();
  Size size = buffer.GetSize();
  for (Size i = 0; i < size; ++i) {
    if (*(cursor + i) != ' ' && *(cursor + i) != '\t' &&
        *(cursor + i) != '\n' && *(cursor + i) != '\r') {
      buffer.SetCursor(cursor + i);
      return;
    }
  }
}

} // namespace TerreateIO::IOController
