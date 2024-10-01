#ifndef __TERREATEIO_MODEL_MESH_HPP__
#define __TERREATEIO_MODEL_MESH_HPP__

#include "../defines.hpp"
#include "material.hpp"
#include "skeleton.hpp"

namespace TerreateIO::Container {
using namespace TerreateIO::Defines;

struct Attribute {
  Ulong size;
  Ulong stride;
  Ulong offset;
};

class Mesh : public TerreateObjectBase {
private:
  Str mName;
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

  Str const &GetName() const { return mName; }
  Map<Str, Vec<Vec<Float>>> const &GetVertexDataComponents() const {
    return mVertexDataComponents;
  }
  Vec<Vec<vec3>> const &GetPositionMorphTargets() const {
    return mPositionMorphTargets;
  }
  Vec<Vec<vec3>> const &GetNormalMorphTargets() const {
    return mNormalMorphTargets;
  }
  Vec<Vec<vec3>> const &GetTangentMorphTargets() const {
    return mTangentMorphTargets;
  }
  Vec<Float> const &GetMorphWeights() const { return mMorphWeights; }
  Vec<Vec<Uint>> const &GetVertexConstructionIndices() const {
    return mVertexConstructionIndices;
  }
  Vec<Vec<Uint>> const &GetFaceIndices() const { return mFaceIndices; }
  Vec<Float> const &GetRawVertexData() const { return mRawVertexData; }
  Vec<Attribute> const &GetRawVertexDataAttributes() const {
    return mRawVertexDataAttributes;
  }
  Uint const &GetMaterial() const { return mMaterial; }

  void SetName(Str const &name) { mName = name; }
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
} // namespace TerreateIO::Container

#endif // __TERREATEIO_MODEL_MESH_HPP__
