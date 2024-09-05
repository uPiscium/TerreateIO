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
#include "json.hpp"

namespace TerreateIO::GLTF {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;
using namespace TerreateCore::Math;

typedef JSON::JSONParser JSONParser;

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
  Nullable<Uint> bufferView;
  Nullable<Uint> byteOffset;
  GLTFComponentType componentType = GLTFComponentType::NONE; // Required
  Bool normalized = false;
  Uint count = 0u;                // Required
  GLTFType type = GLTFType::NONE; // Required
  Float *max = nullptr;
  Float *min = nullptr;
  Str name = "";
  // Sparse sparse; // Sparse accessor is currently not supported
};

struct GLTFAnimationTarget {
  Nullable<Uint> node;
  Str path = ""; // Required
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
  Str copyright = "";
  Str generator = "";
  Str version = ""; // Required
  Str minVersion = "";
};

struct GLTFBuffer {
  Str uri = "";
  Uint byteLength = 0u; // Required
  Str name = "";
};

struct GLTFBufferView {
  Uint buffer = 0u; // Required
  Nullable<Uint> byteOffset;
  Uint byteLength = 0u; // Required
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
  Nullable<Float> aspectRatio;
  Float yfov = 0.0f; // Required
  Nullable<Float> zfar;
  Float znear = 0.0f; // Required
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
  GLTFTextureInfo baseColorTexture;
  Float metallicFactor = 1.0f;
  Float roughnessFactor = 1.0f;
  GLTFTextureInfo metallicRoughnessTexture;
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
  GLTFPBRMetallicRoughness pbrMetallicRoughness;
  GLTFNormalTextureInfo normalTexture;
  GLTFOcclusionTextureInfo occlusionTexture;
  GLTFTextureInfo emissiveTexture;
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
  Nullable<Uint> inverseBindMatrices;
  Nullable<Uint> skeleton;
  Vec<Uint> joints; // Required
  Str name = "";
};

struct GLTFTexture {
  Nullable<Uint> sampler;
  Uint source = 0u; // Required
  Str name = "";
};

struct GLTFRoot {
  Vec<Str> extensionsUsed;
  Vec<Str> extensionsRequired;
  Vec<GLTFAccessor> accessors;
  Vec<GLTFAnimation> animations;
  GLTFAsset asset; // Required
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

class GLTFParser : public ParserBase {
private:
  GLTFRoot mRoot;
};

class GLTFComposer : public ComposerBase {
  ;
};
} // namespace TerreateIO::GLTF

#endif // __TERREATEIO_GLTF_HPP__
