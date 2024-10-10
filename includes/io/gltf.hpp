#ifndef __TERREATEIO_IO_GLTF_HPP__
#define __TERREATEIO_IO_GLTF_HPP__

#include "../buffer.hpp"
#include "constants/gltf.hpp"
#include "interface.hpp"
#include "json.hpp"

namespace TerreateIO::GLTF {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;
using namespace TerreateCore::Math;
using namespace TerreateIO::Container;

namespace JsonUtil = TerreateIO::JSON::Utils;
typedef JSON::JSONParser JSONParser;
typedef JSON::Array Array;
typedef JSON::Object Object;
typedef JSON::JSON JSON;

namespace Utils {
template <typename T>
using EnumConverter = Function<Bool(Str const &src, T &value)>;

GLTFType ToGLTFType(Str const &type);
GLTFInterpolationType ToGLTFInterpolationType(Str const &type);
GLTFCameraType ToGLTFCameraType(Str const &type);
GLTFAlphaMode ToGLTFAlphaMode(Str const &mode);
Uint GetGLTFComponentTypeSize(GLTFComponentType const &compType);
Str ToString(GLTFType const &type);
Str ToString(GLTFInterpolationType const &type);
Str ToString(GLTFCameraType const &type);
Str ToString(GLTFAlphaMode const &mode);

Float Extract(GLTFComponentType const &compType, ReadBuffer &buffer);
template <enumtype T>
Bool Extract(JSON const &json, Str const &key, T &value,
             EnumConverter<T> converter);

template <enumtype T>
Bool Extract(JSON const &json, Str const &key, T &value,
             EnumConverter<T> converter) {
  Str temp;
  if (!JsonUtil::Extract(json, key, temp)) {
    return false;
  }

  return converter(temp, value);
}
} // namespace Utils

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

class GLTFParser : public ParserBase {
private:
  JSON mJsonData;
  GLTFRoot mRoot;
  Mutex mMutex;
  Vec<GLTFObject> mBuffers;

private:
  Bool LoadJson(ReadBuffer &buffer);

  Bool ParseExtensions(JSON const &json);
  Bool ParseExtensionUsed(JSON const &json, Vec<Str> &extensionsUsed);
  Bool ParseExtensionRequired(JSON const &json, Vec<Str> &extensionsRequired);
  Bool ParseAccessors(JSON const &json, Vec<GLTFAccessor> &container);
  Bool ParseAnimationTarget(JSON const &json, GLTFAnimationTarget &container);
  Bool ParseAnimationChannels(JSON const &json,
                              Vec<GLTFAnimationChannel> &container);
  Bool ParseAnimationSamplers(JSON const &json,
                              Vec<GLTFAnimationSampler> &container);
  Bool ParseAnimations(JSON const &json, Vec<GLTFAnimation> &container);
  Bool ParseAsset(JSON const &json, GLTFAsset &container);
  Bool LoadBuffer(GLTFBuffer &buffer);
  Bool ParseBuffers(JSON const &json, Vec<GLTFBuffer> &container);
  Bool ParseBufferViews(JSON const &json, Vec<GLTFBufferView> &container);
  Bool ParseOrthographic(JSON const &json, GLTFOrthographic &container);
  Bool ParsePerspective(JSON const &json, GLTFPerspective &container);
  Bool ParseCameras(JSON const &json, Vec<GLTFCamera> &container);
  Bool ParseImages(JSON const &json, Vec<GLTFImage> &container);
  Bool ParseTextureInfo(JSON const &json, GLTFTextureInfo &container);
  Bool ParseTextureInfo(JSON const &json, Nullable<GLTFTextureInfo> &container);
  Bool ParsePBRMetallicRoughness(JSON const &json,
                                 GLTFPBRMetallicRoughness &container);
  Bool ParsePBRMetallicRoughness(JSON const &json,
                                 Nullable<GLTFPBRMetallicRoughness> &container);
  Bool ParseNormalTextureInfo(JSON const &json,
                              GLTFNormalTextureInfo &container);
  Bool ParseNormalTextureInfo(JSON const &json,
                              Nullable<GLTFNormalTextureInfo> &container);
  Bool ParseOcclusionTextureInfo(JSON const &json,
                                 GLTFOcclusionTextureInfo &container);
  Bool ParseOcclusionTextureInfo(JSON const &json,
                                 Nullable<GLTFOcclusionTextureInfo> &container);
  Bool ParseMaterials(JSON const &json, Vec<GLTFMaterial> &container);
  Bool ParsePrimitives(JSON const &json, Vec<GLTFPrimitive> &container);
  Bool ParseMeshes(JSON const &json, Vec<GLTFMesh> &container);
  Bool ParseNodes(JSON const &json, Vec<GLTFNode> &container);
  Bool ParseSamplers(JSON const &json, Vec<GLTFSampler> &container);
  Bool ParseScenes(JSON const &json, Vec<GLTFScene> &container);
  Bool ParseSkins(JSON const &json, Vec<GLTFSkin> &container);
  Bool ParseTextures(JSON const &json, Vec<GLTFTexture> &container);

public:
  GLTFParser() = default;
  GLTFParser(Str const &path) : ParserBase(path) {}
  ~GLTFParser() = default;

  Str GetGLTFInfo() const;
  GLTFRoot const &GetRoot() const { return mRoot; }

  Bool Parse(ReadBuffer &buffer) override;
  Bool Parse() override;
};

class GLTFImporter : public IImporter {
private:
  GLTFRoot mRoot;
  Scene mScene;
  Vec<GLTFObject> mAccessors;
  Vec<Int> mSkeletonRoots;
  Str mError;
  Bool mImported = false;

private:
  GLTFObject ParseAccessor(GLTFAccessor const &accessor);
  Camera ParseCamera(GLTFCamera const &camera);
  Texture ParseTexture(GLTFTexture const &texture);
  Material ParseMaterial(GLTFMaterial const &material);
  MeshGroup ParseMesh(GLTFMesh const &mesh);
  void ParseNode(Stage &stage, GLTFNode const &node);
  void ParseModel();

public:
  GLTFImporter() {}

  Str const &GetError() override { return mError; }
  Scene const &GetScene() override { return mScene; }

  Bool IsImported() override { return mImported; }

  void Import(Str const &path) override;
};
} // namespace TerreateIO::GLTF
#endif // __TERREATEIO_IO_GLTF_HPP__
