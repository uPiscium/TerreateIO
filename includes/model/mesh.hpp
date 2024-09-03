#ifndef __TERREATEIO_MODEL_MESH_HPP__
#define __TERREATEIO_MODEL_MESH_HPP__

#include "../defines.hpp"
#include "material.hpp"
#include "skeleton.hpp"

namespace TerreateIO::Model {
using namespace TerreateIO::Defines;

struct Attribute {
  Ulong size;
  Ulong stride;
  Ulong offset;
};

class Mesh : public TerreateObjectBase {
private:
  Map<Str, Vec<Vec<Float>>> mVertexDataComponents;
  Vec<Vec<Uint>> mVertexConstructionIndices;
  Vec<Vec<Uint>> mFaceIndices;

  Vec<Float> mRawVertexData;
  Vec<Attribute> mRawVertexDataAttributes;
  Bool mRawData = false;

  Material mMaterial;
  Skeleton mSkeleton;

public:
  Mesh() {}

  Map<Str, Vec<Vec<Float>>> const &GetVertexDataComponents() const {
    return mVertexDataComponents;
  }
  Vec<Vec<Uint>> const &GetVertexConstructionIndices() const {
    return mVertexConstructionIndices;
  }
  Vec<Vec<Uint>> const &GetFaceIndices() const { return mFaceIndices; }
  Vec<Float> const &GetRawVertexData() const { return mRawVertexData; }
  Vec<Attribute> const &GetRawVertexDataAttributes() const {
    return mRawVertexDataAttributes;
  }
  Material const &GetMaterial() const { return mMaterial; }
  Skeleton const &GetSkeleton() const { return mSkeleton; }

  void SetVertexConstructionIndices(Vec<Vec<Uint>> const &indices) {
    mVertexConstructionIndices = indices;
  }
  void SetFaceIndices(Vec<Vec<Uint>> const &indices) { mFaceIndices = indices; }
  void SetRawVertexData(Vec<Float> const &data,
                        Vec<Attribute> const &attributes);
  void SetMaterial(Material const &material) { mMaterial = material; }
  void SetSkeleton(Skeleton const &skeleton) { mSkeleton = skeleton; }

  Bool const &IsRawData() const { return mRawData; }

  void AddVertexDataComponent(Str const &name,
                              Vec<Vec<Float>> const &component);
};
} // namespace TerreateIO::Model

#endif // __TERREATEIO_MODEL_MESH_HPP__
