#ifndef __TERREATEIO_IMPORTER_GLTF_HPP__
#define __TERREATEIO_IMPORTER_GLTF_HPP__

#include <tinygltf/tiny_gltf.h>

#include "interface.hpp"

namespace TerreateIO::GLTF {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;
using namespace TerreateCore::Math;
using namespace TerreateIO::Container;

enum class GLTFType {
  SCALAR,
  VEC2,
  VEC3,
  VEC4,
  MAT2,
  MAT3,
  MAT4,
};

class GLTFObject {
private:
  GLTFType mType;
  Vec<Float> mValue;

public:
  GLTFObject() : mType(GLTFType::SCALAR), mValue({0.0}) {}
  GLTFObject(GLTFType const &type, Vec<Float> const &value)
      : mType(type), mValue(value) {}
  GLTFObject(GLTFObject const &other)
      : mType(other.mType), mValue(other.mValue) {}

  GLTFType const &GetType() const { return mType; }
  Vec<Float> const &GetValue() const { return mValue; }

  Bool IsScalar() const { return mType == GLTFType::SCALAR; }
  Bool IsVec2() const { return mType == GLTFType::VEC2; }
  Bool IsVec3() const { return mType == GLTFType::VEC3; }
  Bool IsVec4() const { return mType == GLTFType::VEC4; }
  Bool IsMat2() const { return mType == GLTFType::MAT2; }
  Bool IsMat3() const { return mType == GLTFType::MAT3; }
  Bool IsMat4() const { return mType == GLTFType::MAT4; }

  template <typename T> Vec<T> AsScalar() const {
    Vec<T> result;
    for (int i = 0; i < mValue.size(); ++i) {
      result.push_back(static_cast<T>(mValue[i]));
    }
    return result;
  }
  Vec<vec2> AsVec2() const;
  Vec<vec3> AsVec3() const;
  Vec<vec4> AsVec4() const;
  Vec<mat2> AsMat2() const;
  Vec<mat3> AsMat3() const;
  Vec<mat4> AsMat4() const;
  Vec<Vec<Float>> AsMatrix() const;

  GLTFObject &operator=(GLTFObject const &other);
  GLTFObject &operator=(Vec<Float> const &value);
  GLTFObject &operator=(Vec<vec2> const &value);
  GLTFObject &operator=(Vec<vec3> const &value);
  GLTFObject &operator=(Vec<vec4> const &value);
  GLTFObject &operator=(Vec<mat2> const &value);
  GLTFObject &operator=(Vec<mat3> const &value);
  GLTFObject &operator=(Vec<mat4> const &value);

  operator Vec<Float>() const { return mValue; }
  operator Vec<vec2>() const { return this->AsVec2(); }
  operator Vec<vec3>() const { return this->AsVec3(); }
  operator Vec<vec4>() const { return this->AsVec4(); }
  operator Vec<mat2>() const { return this->AsMat2(); }
  operator Vec<mat3>() const { return this->AsMat3(); }
  operator Vec<mat4>() const { return this->AsMat4(); }
};

class GLTFImporter : public IImporter {
private:
  tinygltf::Model mModel;
  tinygltf::TinyGLTF mLoader;
  Scene mScene;
  Vec<GLTFObject> mAccessors;
  Vec<Int> mSkeletonRoots;
  Str mError;
  Bool mImported = false;

private:
  GLTFObject ParseAccessor(tinygltf::Accessor const &accessor);
  Camera ParseCamera(tinygltf::Camera const &camera);
  Mesh ParseMesh(tinygltf::Mesh const &mesh);
  void ParseNode(Stage &stage, tinygltf::Node const &node);
  void ParseModel();

public:
  GLTFImporter() {}

  Str const &GetError() override { return mError; }
  Scene const &GetScene() override { return mScene; }

  Bool IsImported() override { return mImported; }

  void Import(Str const &path) override;
};
} // namespace TerreateIO::GLTF

#endif // __TERREATEIO_IMPORTER_GLTF_HPP__
