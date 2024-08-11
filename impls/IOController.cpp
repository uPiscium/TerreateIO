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

  file.write(reinterpret_cast<char const *>(buffer.GetTop()), buffer.GetSize());
  file.close();
}

} // namespace TerreateIO::IOController
