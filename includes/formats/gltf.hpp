#ifndef __TERREATEIO_GLTF_HPP__
#define __TERREATEIO_GLTF_HPP__

////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Currently, this gltf parser is supporting GLTF 2.0 Specification.
 * See the link below for more details.
 * https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#properties-reference
 *
 * TODO:
 * 1. Add support for Sparse accessor
 * 2. Add support for extensions
 * 3. Add support for extras
 */
////////////////////////////////////////////////////////////////////////////////////////////////

#include "base.hpp"
#include "buffer.hpp"
#include "json.hpp"

namespace TerreateIO::GLTF {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;
using namespace TerreateCore::Math;

typedef JSON::JSONParser JSONParser;
typedef JSON::Array Array;
typedef JSON::Object Object;
typedef JSON::JSON JSON;

enum class GLTFComponentType {
  NONE = 0,
  BYTE = 5120,
  UNSIGNED_BYTE = 5121,
  SHORT = 5122,
  UNSIGNED_SHORT = 5123,
  UNSIGNED_INT = 5125,
  FLOAT = 5126
};

enum class GLTFType { NONE, SCALAR, VEC2, VEC3, VEC4, MAT2, MAT3, MAT4 };

enum class GLTFInterpolationType { NONE, LINEAR, STEP, CUBICSPLINE };

enum class GLTFBufferTarget {
  NONE = 0,
  ARRAY_BUFFER = 34962,
  ELEMENT_ARRAY_BUFFER = 34963
};

enum class GLTFCameraType { NONE, PERSPECTIVE, ORTHOGRAPHIC };

enum class GLTFAlphaMode { NONE, OPAQUE, MASK, BLEND };

enum class GLTFPrimitiveMode {
  NONE = 0,
  POINTS = 0,
  LINES = 1,
  LINE_LOOP = 2,
  LINE_STRIP = 3,
  TRIANGLES = 4,
  TRIANGLE_STRIP = 5,
  TRIANGLE_FAN = 6
};

enum class GLTFTextureFilter {
  NONE = 0,
  NEAREST = 9728,
  LINEAR = 9729,
  NEAREST_MIPMAP_NEAREST = 9984,
  LINEAR_MIPMAP_NEAREST = 9985,
  NEAREST_MIPMAP_LINEAR = 9986,
  LINEAR_MIPMAP_LINEAR = 9987
};

enum class GLTFTextureWrapping {
  NONE = 0,
  CLAMP_TO_EDGE = 33071,
  MIRRORED_REPEAT = 33648,
  REPEAT = 10497
};

struct GLTFAccessor {
  GLTFComponentType componentType = GLTFComponentType::NONE; // Required
  Uint count = 0u;                                           // Required
  GLTFType type = GLTFType::NONE;                            // Required
  Nullable<Uint> bufferView;
  Uint byteOffset = 0u;
  Bool normalized = false;
  Vec<Float> max;
  Vec<Float> min;
  Str name = "";
  // Sparse sparse; // Sparse accessor is currently not supported
};

struct GLTFAnimationTarget {
  Str path = ""; // Required
  Nullable<Uint> node;
};

struct GLTFAnimationChannel {
  Uint sampler = 0u;          // Required
  GLTFAnimationTarget target; // Required
};

struct GLTFAnimationSampler {
  Uint input = 0u;  // Required
  Uint output = 0u; // Required
  GLTFInterpolationType interpolation = GLTFInterpolationType::LINEAR;
};

struct GLTFAnimation {
  Vec<GLTFAnimationChannel> channels; // Required
  Vec<GLTFAnimationSampler> samplers; // Required
  Str name = "";
};

struct GLTFAsset {
  Str version = ""; // Required
  Str copyright = "";
  Str generator = "";
  Str minVersion = "";
};

struct GLTFBuffer {
  Uint byteLength = 0u; // Required
  Str uri = "";
  Str name = "";
};

struct GLTFBufferView {
  Uint buffer = 0u;     // Required
  Uint byteLength = 0u; // Required
  Uint byteOffset = 0u;
  Nullable<Uint> byteStride;
  GLTFBufferTarget target = GLTFBufferTarget::NONE;
  Str name = "";
};

struct GLTFOrthographic {
  Float xmag = 0.0f;  // Required
  Float ymag = 0.0f;  // Required
  Float zfar = 0.0f;  // Required
  Float znear = 0.0f; // Required
};

struct GLTFPerspective {
  Float yfov = 0.0f;  // Required
  Float znear = 0.0f; // Required
  Nullable<Float> aspectRatio;
  Nullable<Float> zfar;
};

struct GLTFCamera {
  GLTFOrthographic orthographic;              //[A] One of these is required
  GLTFPerspective perspective;                //[A] One of these is required
  GLTFCameraType type = GLTFCameraType::NONE; // Required
  Str name = "";
};

struct GLTFImage {
  Str uri = "";
  Str mimeType = "";
  Nullable<Uint> bufferView;
  Str name = "";
};

struct GLTFTextureInfo {
  Uint index = 0u; // Required
  Nullable<Uint> texCoord;
};

struct GLTFPBRMetallicRoughness {
  vec4 baseColorFactor = vec4(1.0f);
  Nullable<GLTFTextureInfo> baseColorTexture;
  Float metallicFactor = 1.0f;
  Float roughnessFactor = 1.0f;
  Nullable<GLTFTextureInfo> metallicRoughnessTexture;
};

struct GLTFNormalTextureInfo {
  Uint index = 0u; // Required
  Nullable<Uint> texCoord;
  Float scale = 1.0f;
};

struct GLTFOcclusionTextureInfo {
  Uint index = 0u; // Required
  Nullable<Uint> texCoord;
  Float strength = 1.0f;
};

struct GLTFMaterial {
  Str name = "";
  Nullable<GLTFPBRMetallicRoughness> pbrMetallicRoughness;
  Nullable<GLTFNormalTextureInfo> normalTexture;
  Nullable<GLTFOcclusionTextureInfo> occlusionTexture;
  Nullable<GLTFTextureInfo> emissiveTexture;
  vec3 emissiveFactor = vec3(0.0f);
  GLTFAlphaMode alphaMode = GLTFAlphaMode::OPAQUE;
  Float alphaCutoff = 0.5f;
  Bool doubleSided = false;
};

struct GLTFPrimitive {
  Map<Str, Uint> attributes; // Required
  Nullable<Uint> indices;
  Nullable<Uint> material;
  GLTFPrimitiveMode mode = GLTFPrimitiveMode::TRIANGLES;
  Map<Str, Uint> morphTargets;
};

struct GLTFMesh {
  Vec<GLTFPrimitive> primitives; // Required
  Vec<Float> weights;
  Str name = "";
};

struct GLTFNode {
  Nullable<Uint> camera;
  Vec<Uint> children;
  Nullable<Uint> skin;
  mat4 matrix = identity<mat4>();
  Nullable<Uint> mesh;
  quat rotation = quat(1.0f, 0.0f, 0.0f, 0.0f);
  vec3 scale = vec3(1.0f);
  vec3 translation = vec3(0.0f);
  Vec<Uint> weights;
  Str name = "";
};

struct GLTFSampler {
  GLTFTextureFilter magFilter = GLTFTextureFilter::NONE;
  GLTFTextureFilter minFilter = GLTFTextureFilter::NONE;
  GLTFTextureWrapping wrapS = GLTFTextureWrapping::REPEAT;
  GLTFTextureWrapping wrapT = GLTFTextureWrapping::REPEAT;
  Str name = "";
};

struct GLTFScene {
  Vec<Uint> nodes;
  Str name = "";
};

struct GLTFSkin {
  Vec<Uint> joints; // Required
  Nullable<Uint> inverseBindMatrices;
  Nullable<Uint> skeleton;
  Str name = "";
};

struct GLTFTexture {
  Uint source = 0u; // Required
  Nullable<Uint> sampler;
  Str name = "";
};

struct GLTFRoot {
  GLTFAsset asset; // Required
  Vec<Str> extensionsUsed;
  Vec<Str> extensionsRequired;
  Vec<GLTFAccessor> accessors;
  Vec<GLTFAnimation> animations;
  Vec<GLTFBuffer> buffers;
  Vec<GLTFBufferView> bufferViews;
  Vec<GLTFCamera> cameras;
  Vec<GLTFImage> images;
  Vec<GLTFMaterial> materials;
  Vec<GLTFMesh> meshes;
  Vec<GLTFNode> nodes;
  Vec<GLTFSampler> samplers;
  Nullable<Uint> scene;
  Vec<GLTFScene> scenes;
  Vec<GLTFSkin> skins;
  Vec<GLTFTexture> textures;
};

struct BinaryBuffer {
  ReadBuffer buffer;
  Nullable<Uint> stride;
};

class GLTFDataContainer {
public:
  union Container {
    Vec<Float> *scalarContainer;
    Vec<vec2> *vec2Container;
    Vec<vec3> *vec3Container;
    Vec<vec4> *vec4Container;
    Vec<mat2> *mat2Container;
    Vec<mat3> *mat3Container;
    Vec<mat4> *mat4Container;
  };

private:
  GLTFType mType;
  Container mContainer;

public:
  GLTFDataContainer() : mType(GLTFType::NONE) {
    mContainer.scalarContainer = nullptr;
  }
  GLTFDataContainer(GLTFDataContainer const &container);
  GLTFDataContainer(Float const *data, Uint const size) {
    this->SetData(data, size);
  }
  GLTFDataContainer(Vec<Float> const &data) { this->SetData(data); }
  GLTFDataContainer(vec2 const *data, Uint const size) {
    this->SetData(data, size);
  }
  GLTFDataContainer(Vec<vec2> const &data) { this->SetData(data); }
  GLTFDataContainer(vec3 const *data, Uint const size) {
    this->SetData(data, size);
  }
  GLTFDataContainer(Vec<vec3> const &data) { this->SetData(data); }
  GLTFDataContainer(vec4 const *data, Uint const size) {
    this->SetData(data, size);
  }
  GLTFDataContainer(Vec<vec4> const &data) { this->SetData(data); }
  GLTFDataContainer(mat2 const *data, Uint const size) {
    this->SetData(data, size);
  }
  GLTFDataContainer(Vec<mat2> const &data) { this->SetData(data); }
  GLTFDataContainer(mat3 const *data, Uint const size) {
    this->SetData(data, size);
  }
  GLTFDataContainer(Vec<mat3> const &data) { this->SetData(data); }
  GLTFDataContainer(mat4 const *data, Uint const size) {
    this->SetData(data, size);
  }
  GLTFDataContainer(Vec<mat4> const &data) { this->SetData(data); }
  ~GLTFDataContainer() { this->Clear(); }

  GLTFType GetType() const { return mType; }
  Container GetContainer() const { return mContainer; }
  Vec<Float> const &GetScalarContainer() const {
    return *mContainer.scalarContainer;
  }
  Vec<vec2> const &GetVec2Container() const {
    return *mContainer.vec2Container;
  }
  Vec<vec3> const &GetVec3Container() const {
    return *mContainer.vec3Container;
  }
  Vec<vec4> const &GetVec4Container() const {
    return *mContainer.vec4Container;
  }
  Vec<mat2> const &GetMat2Container() const {
    return *mContainer.mat2Container;
  }
  Vec<mat3> const &GetMat3Container() const {
    return *mContainer.mat3Container;
  }
  Vec<mat4> const &GetMat4Container() const {
    return *mContainer.mat4Container;
  }

  Bool IsScalar() const { return mType == GLTFType::SCALAR; }
  Bool IsVec2() const { return mType == GLTFType::VEC2; }
  Bool IsVec3() const { return mType == GLTFType::VEC3; }
  Bool IsVec4() const { return mType == GLTFType::VEC4; }
  Bool IsMat2() const { return mType == GLTFType::MAT2; }
  Bool IsMat3() const { return mType == GLTFType::MAT3; }
  Bool IsMat4() const { return mType == GLTFType::MAT4; }

  void SetData(Float const *data, Uint const size);
  void SetData(Vec<Float> const &data) {
    this->SetData(data.data(), data.size());
  }
  void SetData(vec2 const *data, Uint const size);
  void SetData(Vec<vec2> const &data) {
    this->SetData(data.data(), data.size());
  }
  void SetData(vec3 const *data, Uint const size);
  void SetData(Vec<vec3> const &data) {
    this->SetData(data.data(), data.size());
  }
  void SetData(vec4 const *data, Uint const size);
  void SetData(Vec<vec4> const &data) {
    this->SetData(data.data(), data.size());
  }
  void SetData(mat2 const *data, Uint const size);
  void SetData(Vec<mat2> const &data) {
    this->SetData(data.data(), data.size());
  }
  void SetData(mat3 const *data, Uint const size);
  void SetData(Vec<mat3> const &data) {
    this->SetData(data.data(), data.size());
  }
  void SetData(mat4 const *data, Uint const size);
  void SetData(Vec<mat4> const &data) {
    this->SetData(data.data(), data.size());
  }

  void Clear();

  Bool Empty() const;
  Uint Size() const;
};

namespace Utils {
template <typename T>
using EnumConverter = std::function<Bool(Str const &src, T &value)>;

template <typename T>
concept number = std::is_arithmetic_v<T>;

Bool Extract(JSON const &json, Str const &key, JSON &value);
Bool Extract(JSON const &json, Str const &key, Bool &value);
Bool Extract(JSON const &json, Str const &key, Double &value);
Bool Extract(JSON const &json, Str const &key, Str &value);
Bool Extract(JSON const &json, Str const &key, Array &value);
Bool Extract(JSON const &json, Str const &key, Object &value);

Bool Extract(JSON const &json, Str const &key, Vec<Bool> &value);
Bool Extract(JSON const &json, Str const &key, Vec<Double> &value);
Bool Extract(JSON const &json, Str const &key, Vec<Str> &value);

Bool Extract(JSON const &json, Str const &key, Map<Str, Bool> &value);
Bool Extract(JSON const &json, Str const &key, Map<Str, Double> &value);
Bool Extract(JSON const &json, Str const &key, Map<Str, Str> &value);

template <enumtype T> Bool Extract(JSON const &json, Str const &key, T &value);
template <enumtype T>
Bool Extract(JSON const &json, Str const &key, T &value,
             EnumConverter<T> converter);
template <number T> Bool Extract(JSON const &json, Str const &key, T &value);
template <number T>
Bool Extract(JSON const &json, Str const &key, Vec<T> &value);
template <number T>
Bool Extract(JSON const &json, Str const &key, Nullable<T> &value);
template <number T>
Bool Extract(JSON const &json, Str const &key, Map<Str, T> &value);
template <typename T>
Bool Extract(JSON const &json, Str const &key, Nullable<T> &value);

template <enumtype T> Bool Extract(JSON const &json, Str const &key, T &value) {
  Double temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  value = static_cast<T>(temp);
  return true;
}

template <enumtype T>
Bool Extract(JSON const &json, Str const &key, T &value,
             EnumConverter<T> converter) {
  Str temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  return converter(temp, value);
}

template <number T> Bool Extract(JSON const &json, Str const &key, T &value) {
  Double temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  value = static_cast<T>(temp);
  return true;
}

template <number T>
Bool Extract(JSON const &json, Str const &key, Vec<T> &value) {
  Vec<Double> temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  value.resize(temp.size());
  for (Uint i = 0; i < temp.size(); ++i) {
    value[i] = static_cast<T>(temp[i]);
  }

  return true;
}

template <number T>
Bool Extract(JSON const &json, Str const &key, Nullable<T> &value) {
  T temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  value = temp;
  return true;
}

template <number T>
Bool Extract(JSON const &json, Str const &key, Map<Str, T> &value) {
  Map<Str, Double> temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  for (auto const &[k, v] : temp) {
    value.insert({k, static_cast<T>(v)});
  }

  return true;
}

template <typename T>
Bool Extract(JSON const &json, Str const &key, Nullable<T> &value) {
  T temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  value = temp;
  return true;
}

GLTFType ToGLTFType(Str const &type);
GLTFInterpolationType ToGLTFInterpolationType(Str const &type);
GLTFCameraType ToGLTFCameraType(Str const &type);
GLTFAlphaMode ToGLTFAlphaMode(Str const &mode);
Str ToString(GLTFType const &type);
Str ToString(GLTFInterpolationType const &type);
Str ToString(GLTFCameraType const &type);
Str ToString(GLTFAlphaMode const &mode);

Uint GetGLTFComponentTypeSize(GLTFComponentType const &compType);
void Extract(Float &value, GLTFComponentType const &compType,
             ReadBuffer &buffer);
} // namespace Utils

class GLTFParser : public ParserBase {
private:
  enum class ParseTargets {
    ACCESSORS,
    ANIMATIONS,
    ASSET,
    BUFFERS,
    BUFFER_VIEWS,
    CAMERAS,
    IMAGES,
    MATERIALS,
    MESHES,
    NODES,
    SAMPLERS,
    SCENES,
    SKINS,
    TEXTURES
  };

private:
  JSON mJsonData;
  Executor mExecutor;
  GLTFRoot mRoot;
  Mutex mMutex;
  Vec<GLTFDataContainer> mDataContainers;
  Map<ParseTargets, Bool> mParsingStatus;

private:
  Bool LoadJson(ReadBuffer &buffer);

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

  void LoadBuffers(Vec<BinaryBuffer> &container);
  void ParseScalar(GLTFAccessor const &accessor, BinaryBuffer &buffer,
                   GLTFDataContainer &container);
  void ParseVec2(GLTFAccessor const &accessor, BinaryBuffer &buffer,
                 GLTFDataContainer &container);
  void ParseVec3(GLTFAccessor const &accessor, BinaryBuffer &buffer,
                 GLTFDataContainer &container);
  void ParseVec4(GLTFAccessor const &accessor, BinaryBuffer &buffer,
                 GLTFDataContainer &container);
  void ParseMat2(GLTFAccessor const &accessor, BinaryBuffer &buffer,
                 GLTFDataContainer &container);
  void ParseMat3(GLTFAccessor const &accessor, BinaryBuffer &buffer,
                 GLTFDataContainer &container);
  void ParseMat4(GLTFAccessor const &accessor, BinaryBuffer &buffer,
                 GLTFDataContainer &container);
  void ParseBufferData(Vec<GLTFDataContainer> &container);
  void ParseBinary();

  Handle ParseGLTFMetadata();

public:
  GLTFParser() = default;
  GLTFParser(Str const &path) : ParserBase(path) {}
  ~GLTFParser() = default;

  Str GetGLTFInfo() const;

  Bool Parse(ReadBuffer &buffer) override;
  Bool Parse() override;
};

class GLTFComposer : public ComposerBase {
  ;
};
} // namespace TerreateIO::GLTF

#endif // __TERREATEIO_GLTF_HPP__
