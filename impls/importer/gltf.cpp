#include "../../includes/importer/gltf.hpp"
#include "../exceptions.hpp"

namespace TerreateIO::GLTF {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;
using namespace TerreateCore::Math;
using namespace TerreateIO::Container;

Camera GLTFImporter::ParseCamera(tinygltf::Camera const &camera) {
  Camera result;
  if (camera.type == "perspective") {
    result.SetType(CameraType::PERSPECTIVE);
    result.SetFov(camera.perspective.yfov);
    result.SetNear(camera.perspective.znear);
    result.SetFar(camera.perspective.zfar);
    Double ratio = camera.perspective.aspectRatio;
    result.SetSize({1.0, 1.0 / ratio});
  } else if (camera.type == "orthographic") {
    result.SetType(CameraType::ORTHOGRAPHIC);
    result.SetWidth(camera.orthographic.xmag);
    result.SetHeight(camera.orthographic.ymag);
    result.SetNear(camera.orthographic.znear);
    result.SetFar(camera.orthographic.zfar);
  }
  return result;
}

void GLTFImporter::ParseNode(Stage &stage, tinygltf::Node const &node) {
  if (node.camera != -1) {
    stage.AddCamera(this->ParseCamera(mModel.cameras[node.camera]));
  }
}

void GLTFImporter::ParseModel() {
  if (!mImported) {
    throw Exception::GLTFException("Model not imported");
  }

  Vec<Int> skeletonRoots;
  for (auto &skin : mModel.skins) {
    skeletonRoots.push_back(skin.skeleton);
  }

  for (auto &scene : mModel.scenes) {
    Stage stage;
    for (auto &node : scene.nodes) {
      if (std::find(skeletonRoots.begin(), skeletonRoots.end(), node) !=
          skeletonRoots.end()) { // Skip skeleton roots
        continue;
      }

      this->ParseNode(stage, mModel.nodes[node]);
    }
  }
}

void GLTFImporter::Import(Str const &path) {
  mLoader.LoadASCIIFromFile(&mModel, &mError, nullptr, path.c_str());
  mImported = true;
}

} // namespace TerreateIO::GLTF
