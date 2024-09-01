#ifndef __TERREATEIO_SCENE_HPP__
#define __TERREATEIO_SCENE_HPP__

#include "defines.hpp"
#include "model/camera.hpp"
#include "model/mesh.hpp"

namespace TerreateIO::Scene {
using namespace TerreateIO::Defines;

class Stage : public TerreateObjectBase {
private:
  Vec<Stage> mChildren;
  Vec<Model::Camera> mCameras;
};

class Scene : public TerreateObjectBase {
private:
  Vec<Model::Mesh> mMeshes;
};
} // namespace TerreateIO::Scene

#endif // __TERREATEIO_SCENE_HPP__
