#ifndef __TERREATEIO_IMPORTER_GLTF_HPP__
#define __TERREATEIO_IMPORTER_GLTF_HPP__

#include <tinygltf/tiny_gltf.h>

#include "interface.hpp"

namespace TerreateIO::GLTF {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;
using namespace TerreateCore::Math;
using namespace TerreateIO::Container;

class GLTFImporter : public IImporter {
private:
  tinygltf::Model mModel;
  tinygltf::TinyGLTF mLoader;
  Scene mScene;
  Str mError;
  Bool mImported = false;

private:
  Camera ParseCamera(tinygltf::Camera const &camera);
  void ParseNode(Stage &stage, tinygltf::Node const &node);
  void ParseModel();

public:
  GLTFImporter() {}

  Str const &GetError() override { return mError; }
  Scene const &GetScene() override { return mScene; }

  Bool IsImported() override { return mImported; }

  void Import(Str const &path) override;
};
} // namespace TerreateIO::GLTF

#endif // __TERREATEIO_IMPORTER_GLTF_HPP__
