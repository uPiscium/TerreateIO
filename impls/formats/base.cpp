#include "../../includes/formats/base.hpp"
#include "../../includes/exceptions.hpp"

namespace TerreateIO::Core {
using namespace TerreateIO::Defines;

ParserBase::ParserBase(Str const &path) : mFilePath(path) {
  auto slash = mFilePath.find_first_of('/');
  mParent = mFilePath.substr(0, mFilePath.find_last_of('/'));
  Str copy = mFilePath;
  while (slash != Str::npos) {
    mPath.push_back(copy.substr(0, slash));
    copy = copy.substr(slash + 1);
    slash = copy.find_first_of('/');
  }
}

ReadBuffer ParserBase::LoadFile(Str const &path) {
  InputFileStream file(path);
  if (!file.is_open()) {
    throw Exception::ParserException("Failed to open file: " + path);
  }

  Stream tempBuffer;
  tempBuffer << file.rdbuf();
  return ReadBuffer(tempBuffer.str());
}

Str ParserBase::Escape(Byte const &chr) {
  switch (chr) {
  case '"':
    return "\\\"";
  case '\\':
    return "\\\\";
  case '\b':
    return "\\b";
  case '\f':
    return "\\f";
  case '\n':
    return "\\n";
  case '\r':
    return "\\r";
  case '\t':
    return "\\t";
  default:
    Str buf;
    buf += chr;
    return buf;
  }
}

Str ParserBase::Unescape(Byte const &chr) {
  Str buf;
  switch (chr) {
  case '"':
    buf += '\"';
    break;
  case '\\':
    buf += '\\';
    break;
  case 'b':
    buf += '\b';
    break;
  case 'f':
    buf += '\f';
    break;
  case 'n':
    buf += '\n';
    break;
  case 'r':
    buf += '\r';
    break;
  case 't':
    buf += '\t';
    break;
  default:
    buf += chr;
    break;
  }
  return buf;
}

void ComposerBase::SaveFile(Str const &path, WriteBuffer const &buffer) {
  OutputFileStream file(path);
  if (!file.is_open()) {
    throw Exception::ComposerException("Failed to open file: " + path);
  }

  file << buffer.Dump();
}
} // namespace TerreateIO::Core
