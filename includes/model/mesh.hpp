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
  Str mName;
  Map<Str, Vec<Vec<Float>>> mVertexDataComponents;
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
};
} // namespace TerreateIO::Model

#endif // __TERREATEIO_MODEL_MESH_HPP__
