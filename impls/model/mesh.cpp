#include "../../includes/model/mesh.hpp"

namespace TerreateIO::Model {
using namespace TerreateIO::Defines;

void Mesh::SetRawVertexData(Vec<Float> const &data,
                            Vec<Attribute> const &attributes) {
  mRawVertexData = data;
  mRawVertexDataAttributes = attributes;
  mRawData = true;
}

void Mesh::AddVertexDataComponent(Str const &name,
                                  Vec<Vec<Float>> const &component) {
  if (mVertexDataComponents.find(name) == mVertexDataComponents.end()) {
    mVertexDataComponents.insert({name, component});
  } else {
    mVertexDataComponents[name] = component;
  }
}
} // namespace TerreateIO::Model
