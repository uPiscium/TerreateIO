#ifndef __TERREATEIO_SCENE_HPP__
#define __TERREATEIO_SCENE_HPP__

#include "defines.hpp"
#include "model/animation.hpp"
#include "model/camera.hpp"
#include "model/mesh.hpp"

namespace TerreateIO::Scene {
using namespace TerreateIO::Defines;

class Stage : public TerreateObjectBase {
private:
  Vec<Stage> mChildren;
  Vec<Model::Camera> mCameras;
  Vec<Uint> mMeshIndices;

public:
  Stage() = default;
  Stage(Stage const &stage) = default;

  Vec<Stage> const &GetChildren() const { return mChildren; }
  Vec<Model::Camera> const &GetCameras() const { return mCameras; }
  Vec<Uint> const &GetMeshIndices() const { return mMeshIndices; }

  void AddChild(Stage const &child) { mChildren.push_back(child); }
  void AddCamera(Model::Camera const &camera) { mCameras.push_back(camera); }
  void AddMeshIndex(Uint const &index) { mMeshIndices.push_back(index); }

  Stage const &operator[](Uint const &index) const { return mChildren[index]; }
  Stage &operator[](Uint const &index) { return mChildren[index]; }
  Stage &operator=(Stage const &stage) = default;
};

class Scene : public TerreateObjectBase {
private:
  Vec<Model::Mesh> mMeshes;
  Vec<Model::Animation> mAnimations;

public:
  Scene() = default;
  Scene(Scene const &scene) = default;

  Vec<Model::Mesh> const &GetMeshes() const { return mMeshes; }
  Vec<Model::Animation> const &GetAnimations() const { return mAnimations; }

  void AddMesh(Model::Mesh const &mesh) { mMeshes.push_back(mesh); }
  void AddAnimation(Model::Animation const &animation) {
    mAnimations.push_back(animation);
  }

  Model::Mesh const &operator[](Uint const &index) const {
    return mMeshes[index];
  }
  Model::Mesh &operator[](Uint const &index) { return mMeshes[index]; }
  Scene &operator=(Scene const &scene) = default;
};
} // namespace TerreateIO::Scene

#endif // __TERREATEIO_SCENE_HPP__
