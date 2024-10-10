#ifndef __TERREATEIO_IO_CONSTANTS_GLTF_HPP__
#define __TERREATEIO_IO_CONSTANTS_GLTF_HPP__

#include "../../buffer.hpp"
#include "../../container/material.hpp"

namespace TerreateIO::GLTF {
using namespace TerreateIO::Defines;
using namespace TerreateCore::Math;

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

enum class GLTFAlphaMode { OPAQUE, MASK, BLEND };

enum class GLTFMimeType { PNG, JPEG };

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
  Core::ReadBuffer data;
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
  GLTFMimeType mimeType = GLTFMimeType::PNG;
  Nullable<Uint> bufferView;
  Str name = "";
  Container::Texture texture;
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
  Vec<Map<Str, Uint>> targets;
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
  GLTFTextureFilter magFilter = GLTFTextureFilter::LINEAR;
  GLTFTextureFilter minFilter = GLTFTextureFilter::LINEAR_MIPMAP_LINEAR;
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
} // namespace TerreateIO::GLTF
#endif // __TERREATEIO_IO_CONSTANTS_GLTF_HPP__
