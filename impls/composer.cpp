#include "../includes/composer.hpp"
#include "../includes/exceptions.hpp"

namespace TerreateIO::Composer {
using namespace TerreateIO::Defines;

void ComposerBase::SaveFile(Str const &path,
                            Buffer::WriteBuffer const &buffer) {
  OutputFileStream file(path);
  if (!file.is_open()) {
    throw Exception::ComposerException("Failed to open file: " + path);
  }

  file << buffer.Dump();
}
} // namespace TerreateIO::Composer
