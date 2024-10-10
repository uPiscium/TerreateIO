#ifndef __TERREATEIO_CONTAINER_SCENE_HPP__
#define __TERREATEIO_CONTAINER_SCENE_HPP__

#include "../defines.hpp"
#include "animation.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "mesh.hpp"

namespace TerreateIO::Container {
using namespace TerreateIO::Defines;

class Stage : public TerreateObjectBase {
private:
  Str mName;
  Vec<Stage> mChildren;
  Vec<Camera> mCameras;
  Vec<Uint> mMeshIndices;
  mat4 mTransform;

public:
  Stage() = default;
  Stage(Stage const &stage) = default;

  Str const &GetName() const { return mName; }
  Vec<Stage> const &GetChildren() const { return mChildren; }
  Vec<Camera> const &GetCameras() const { return mCameras; }
  Vec<Uint> const &GetMeshIndices() const { return mMeshIndices; }
  mat4 const &GetTransform() const { return mTransform; }

  void SetName(Str const &name) { mName = name; }
  void SetTransform(mat4 const &transform) { mTransform = transform; }

  void AddChild(Stage const &child) { mChildren.push_back(child); }
  void AddCamera(Camera const &camera) { mCameras.push_back(camera); }
  void AddMeshIndex(Uint const &index) { mMeshIndices.push_back(index); }

  Stage const &operator[](Uint const &index) const { return mChildren[index]; }
  Stage &operator[](Uint const &index) { return mChildren[index]; }
  Stage &operator=(Stage const &stage) = default;
};

class Scene : public TerreateObjectBase {
private:
  Str mName;
  Vec<MeshGroup> mMeshes;
  Vec<Stage> mStages;
  Vec<Animation> mAnimations;
  Vec<Material> mMaterials;

public:
  Scene() = default;
  Scene(Scene const &scene) = default;

  Str const &GetName() const { return mName; }
  Vec<MeshGroup> const &GetMeshes() const { return mMeshes; }
  Vec<Animation> const &GetAnimations() const { return mAnimations; }
  Vec<Stage> const &GetStages() const { return mStages; }
  Vec<Material> const &GetMaterials() const { return mMaterials; }

  void SetName(Str const &name) { mName = name; }

  void AddMesh(MeshGroup const &mesh) { mMeshes.push_back(mesh); }
  void AddStage(Stage const &stage) { mStages.push_back(stage); }
  void AddAnimation(Animation const &animation) {
    mAnimations.push_back(animation);
  }
  void AddMaterial(Material const &material) { mMaterials.push_back(material); }

  MeshGroup const &operator[](Uint const &index) const {
    return mMeshes[index];
  }
  MeshGroup &operator[](Uint const &index) { return mMeshes[index]; }
  Scene &operator=(Scene const &scene) = default;
};
} // namespace TerreateIO::Container

#endif // __TERREATEIO_CONTAINER_SCENE_HPP__
