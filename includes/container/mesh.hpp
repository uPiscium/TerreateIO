#ifndef __TERREATEIO_MODEL_MESH_HPP__
#define __TERREATEIO_MODEL_MESH_HPP__

#include "../defines.hpp"

namespace TerreateIO::Container {
using namespace TerreateIO::Defines;
using namespace TerreateCore::Math;

struct Attribute {
  Ulong size;
  Ulong stride;
  Ulong offset;
};

class Mesh : public TerreateObjectBase {
private:
  Map<Str, Vec<Vec<Float>>> mVertexDataComponents;
  Vec<Vec<vec3>> mPositionMorphTargets;
  Vec<Vec<vec3>> mNormalMorphTargets;
  Vec<Vec<vec3>> mTangentMorphTargets;
  Vec<Float> mMorphWeights;
  Vec<Vec<Uint>> mVertexConstructionIndices;
  Vec<Vec<Uint>> mFaceIndices;

  Vec<Float> mRawVertexData;
  Vec<Attribute> mRawVertexDataAttributes;
  Bool mRawData = false;

  Uint mMaterial = 0u;

public:
  Mesh() {}

  Map<Str, Vec<Vec<Float>>> const &GetVertexDataComponents() const {
    return mVertexDataComponents;
  }
  Vec<Vec<vec3>> const &GetPositionMorphTargets() const {
    return mPositionMorphTargets;
  }
  Vec<vec3> const &GetPositionMorphTarget(Uint const &index) const {
    return mPositionMorphTargets.at(index);
  }
  Vec<Vec<vec3>> const &GetNormalMorphTargets() const {
    return mNormalMorphTargets;
  }
  Vec<vec3> const &GetNormalMorphTarget(Uint const &index) const {
    return mNormalMorphTargets.at(index);
  }
  Vec<Vec<vec3>> const &GetTangentMorphTargets() const {
    return mTangentMorphTargets;
  }
  Vec<vec3> const &GetTangentMorphTarget(Uint const &index) const {
    return mTangentMorphTargets.at(index);
  }
  Vec<Float> const &GetMorphWeights() const { return mMorphWeights; }
  Float const &GetMorphWeight(Uint const &index) const {
    return mMorphWeights.at(index);
  }
  Vec<Vec<Uint>> const &GetVertexConstructionIndices() const {
    return mVertexConstructionIndices;
  }
  Vec<Vec<Uint>> const &GetFaceIndices() const { return mFaceIndices; }
  Vec<Float> const &GetRawVertexData() const { return mRawVertexData; }
  Vec<Attribute> const &GetRawVertexDataAttributes() const {
    return mRawVertexDataAttributes;
  }
  Uint const &GetMaterial() const { return mMaterial; }

  void SetVertexConstructionIndices(Vec<Vec<Uint>> const &indices) {
    mVertexConstructionIndices = indices;
  }
  void SetFaceIndices(Vec<Vec<Uint>> const &indices) { mFaceIndices = indices; }
  void SetRawVertexData(Vec<Float> const &data,
                        Vec<Attribute> const &attributes);
  void SetMaterial(Uint const &material) { mMaterial = material; }

  Bool const &IsRawData() const { return mRawData; }

  void AddVertexDataComponent(Str const &name,
                              Vec<Vec<Float>> const &component);
  void AddPositionMorphTarget(Vec<vec3> const &target) {
    mPositionMorphTargets.push_back(target);
  }
  void AddNormalMorphTarget(Vec<vec3> const &target) {
    mNormalMorphTargets.push_back(target);
  }
  void AddTangentMorphTarget(Vec<vec3> const &target) {
    mTangentMorphTargets.push_back(target);
  }
  void AddMorphWeight(Float const &weight) { mMorphWeights.push_back(weight); }
};

class MeshGroup : public TerreateObjectBase {
private:
  Str mName;
  Vec<Mesh> mMeshes;

public:
  MeshGroup() {}

  Str const &GetName() const { return mName; }
  Vec<Mesh> const &GetMeshes() const { return mMeshes; }

  void SetName(Str const &name) { mName = name; }

  void AddMesh(Mesh const &mesh) { mMeshes.push_back(mesh); }
};
} // namespace TerreateIO::Container

#endif // __TERREATEIO_MODEL_MESH_HPP__
