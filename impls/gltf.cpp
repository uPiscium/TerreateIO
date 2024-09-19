#include "../includes/gltf.hpp"
#include "../includes/exceptions.hpp"

namespace TerreateIO::GLTF {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;
using namespace TerreateCore::Math;
using namespace TerreateIO::Scene;

void GLTFImporter::ParseModel() {
  if (!mImported) {
    throw Exception::GLTFException("Model not imported");
  }
}

void GLTFImporter::Import(Str const &path) {
  mLoader.LoadASCIIFromFile(&mModel, nullptr, nullptr, path);
  mImported = true;
}

} // namespace TerreateIO::GLTF
