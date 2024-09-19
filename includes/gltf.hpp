#ifndef __TERREATEIO_GLTF_HPP__
#define __TERREATEIO_GLTF_HPP__

#include <tinygltf/tiny_gltf.h>

#include "interface.hpp"
#include "scene.hpp"

namespace TerreateIO::GLTF {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;
using namespace TerreateCore::Math;

class GLTFImporter : public IImporter {
private:
  tinygltf::Model mModel;
  tinygltf::TinyGLTF mLoader;
  Scene::Scene mScene;
  Bool mImported = false;

private:
  void ParseModel();

public:
  GLTFImporter() {}

  Scene::Scene const &GetScene() override { return mScene; }

  Bool IsImported() override { return mImported; }

  void Import(Str const &path) override;
};

class GLTFExporter : public IExporter {
private:
  tinygltf::Model mModel;
  tinygltf::TinyGLTF mLoader;
  Bool mExported = false;

public:
  GLTFExporter() {}

  Bool IsExported() override { return mExported; }

  void Export(Str const &path, Scene::Scene const &scene) override;
};

} // namespace TerreateIO::GLTF

#endif // __TERREATEIO_GLTF_HPP__
