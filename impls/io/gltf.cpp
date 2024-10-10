#include "../../includes/io/gltf.hpp"
#include "../exceptions.hpp"

#include <iostream>

namespace TerreateIO::GLTF {
using namespace TerreateIO::Defines;
using namespace TerreateCore::Math;

namespace Utils {
GLTFType ToGLTFType(Str const &type) {
  if (type == "SCALAR") {
    return GLTFType::SCALAR;
  } else if (type == "VEC2") {
    return GLTFType::VEC2;
  } else if (type == "VEC3") {
    return GLTFType::VEC3;
  } else if (type == "VEC4") {
    return GLTFType::VEC4;
  } else if (type == "MAT2") {
    return GLTFType::MAT2;
  } else if (type == "MAT3") {
    return GLTFType::MAT3;
  } else if (type == "MAT4") {
    return GLTFType::MAT4;
  } else {
    throw Exception::GLTFException("Invalid type");
  }
}

GLTFInterpolationType ToGLTFInterpolationType(Str const &type) {
  if (type == "LINEAR") {
    return GLTFInterpolationType::LINEAR;
  } else if (type == "STEP") {
    return GLTFInterpolationType::STEP;
  } else if (type == "CUBICSPLINE") {
    return GLTFInterpolationType::CUBICSPLINE;
  } else {
    throw Exception::GLTFException("Invalid interpolation type");
  }
}

GLTFCameraType ToGLTFCameraType(Str const &type) {
  if (type == "perspective") {
    return GLTFCameraType::PERSPECTIVE;
  } else if (type == "orthographic") {
    return GLTFCameraType::ORTHOGRAPHIC;
  } else {
    throw Exception::GLTFException("Invalid camera type");
  }
}

GLTFAlphaMode ToGLTFAlphaMode(Str const &mode) {
  if (mode == "OPAQUE") {
    return GLTFAlphaMode::OPAQUE;
  } else if (mode == "MASK") {
    return GLTFAlphaMode::MASK;
  } else if (mode == "BLEND") {
    return GLTFAlphaMode::BLEND;
  } else {
    throw Exception::GLTFException("Invalid alpha mode");
  }
}

Str ToString(GLTFType const &type) {
  switch (type) {
  case GLTFType::SCALAR:
    return "SCALAR";
  case GLTFType::VEC2:
    return "VEC2";
  case GLTFType::VEC3:
    return "VEC3";
  case GLTFType::VEC4:
    return "VEC4";
  case GLTFType::MAT2:
    return "MAT2";
  case GLTFType::MAT3:
    return "MAT3";
  case GLTFType::MAT4:
    return "MAT4";
  default:
    throw Exception::GLTFException("Invalid type");
  }
}

Str ToString(GLTFInterpolationType const &type) {
  switch (type) {
  case GLTFInterpolationType::LINEAR:
    return "LINEAR";
  case GLTFInterpolationType::STEP:
    return "STEP";
  case GLTFInterpolationType::CUBICSPLINE:
    return "CUBICSPLINE";
  default:
    throw Exception::GLTFException("Invalid interpolation type");
  }
}

Str ToString(GLTFCameraType const &type) {
  switch (type) {
  case GLTFCameraType::PERSPECTIVE:
    return "perspective";
  case GLTFCameraType::ORTHOGRAPHIC:
    return "orthographic";
  default:
    throw Exception::GLTFException("Invalid camera type");
  }
}

Str ToString(GLTFAlphaMode const &mode) {
  switch (mode) {
  case GLTFAlphaMode::OPAQUE:
    return "OPAQUE";
  case GLTFAlphaMode::MASK:
    return "MASK";
  case GLTFAlphaMode::BLEND:
    return "BLEND";
  default:
    throw Exception::GLTFException("Invalid alpha mode");
  }
}

Uint GetGLTFComponentTypeSize(GLTFComponentType const &compType) {
  switch (compType) {
  case GLTFComponentType::BYTE:
    return sizeof(Byte);
  case GLTFComponentType::UNSIGNED_BYTE:
    return sizeof(Ubyte);
  case GLTFComponentType::SHORT:
    return sizeof(Short);
  case GLTFComponentType::UNSIGNED_SHORT:
    return sizeof(Ushort);
  case GLTFComponentType::UNSIGNED_INT:
    return sizeof(Uint);
  case GLTFComponentType::FLOAT:
    return sizeof(Float);
  default:
    throw Exception::GLTFException("Invalid component type");
  }
}

Float Extract(GLTFComponentType const &compType, ReadBuffer &buffer) {
  Float value;
  switch (compType) {
  case GLTFComponentType::BYTE:
    value = static_cast<Float>(buffer.Read<Byte>());
    break;
  case GLTFComponentType::UNSIGNED_BYTE:
    value = static_cast<Float>(buffer.Read<Ubyte>());
    break;
  case GLTFComponentType::SHORT:
    value = static_cast<Float>(buffer.Read<Short>());
    break;
  case GLTFComponentType::UNSIGNED_SHORT:
    value = static_cast<Float>(buffer.Read<Ushort>());
    break;
  case GLTFComponentType::UNSIGNED_INT:
    value = static_cast<Float>(buffer.Read<Uint>());
    break;
  case GLTFComponentType::FLOAT:
    value = buffer.Read<Float>();
    break;
  default:
    throw Exception::GLTFException("Invalid component type");
  }
  return value;
}
} // namespace Utils

Vec<vec2> GLTFObject::AsVec2() const {
  if (this->IsVec2()) {
    Vec<vec2> result;
    for (int i = 0; i < mValue.size(); i += 2) {
      result.push_back({mValue[i], mValue[i + 1]});
    }
    return result;
  } else {
    throw Exception::GLTFException("GLTFObject is not a vec2");
  }
}

Vec<vec3> GLTFObject::AsVec3() const {
  if (this->IsVec3()) {
    Vec<vec3> result;
    for (int i = 0; i < mValue.size(); i += 3) {
      result.push_back({mValue[i], mValue[i + 1], mValue[i + 2]});
    }
    return result;
  } else {
    throw Exception::GLTFException("GLTFObject is not a vec3");
  }
}

Vec<vec4> GLTFObject::AsVec4() const {
  if (this->IsVec4()) {
    Vec<vec4> result;
    for (int i = 0; i < mValue.size(); i += 4) {
      result.push_back(
          {mValue[i], mValue[i + 1], mValue[i + 2], mValue[i + 3]});
    }
    return result;
  } else {
    throw Exception::GLTFException("GLTFObject is not a vec4");
  }
}

Vec<mat2> GLTFObject::AsMat2() const {
  if (this->IsMat2()) {
    Vec<mat2> result;
    for (int i = 0; i < mValue.size(); i += 4) {
      result.push_back(
          {mValue[i], mValue[i + 1], mValue[i + 2], mValue[i + 3]});
    }
    return result;
  } else {
    throw Exception::GLTFException("GLTFObject is not a mat2");
  }
}

Vec<mat3> GLTFObject::AsMat3() const {
  if (this->IsMat3()) {
    Vec<mat3> result;
    for (int i = 0; i < mValue.size(); i += 9) {
      result.push_back({mValue[i], mValue[i + 1], mValue[i + 2], mValue[i + 3],
                        mValue[i + 4], mValue[i + 5], mValue[i + 6],
                        mValue[i + 7], mValue[i + 8]});
    }
    return result;
  } else {
    throw Exception::GLTFException("GLTFObject is not a mat3");
  }
}

Vec<mat4> GLTFObject::AsMat4() const {
  if (this->IsMat4()) {
    Vec<mat4> result;
    for (int i = 0; i < mValue.size(); i += 16) {
      result.push_back({mValue[i], mValue[i + 1], mValue[i + 2], mValue[i + 3],
                        mValue[i + 4], mValue[i + 5], mValue[i + 6],
                        mValue[i + 7], mValue[i + 8], mValue[i + 9],
                        mValue[i + 10], mValue[i + 11], mValue[i + 12],
                        mValue[i + 13], mValue[i + 14], mValue[i + 15]});
    }
    return result;
  } else {
    throw Exception::GLTFException("GLTFObject is not a mat4");
  }
}

Vec<Vec<Float>> GLTFObject::AsMatrix() const {
  Vec<Vec<Float>> result;
  Uint size = 0;
  if (this->IsVec2()) {
    size = 2;
  } else if (this->IsVec3()) {
    size = 3;
  } else if (this->IsVec4() || this->IsMat2()) {
    size = 4;
  } else if (this->IsMat3()) {
    size = 9;
  } else if (this->IsMat4()) {
    size = 16;
  } else {
    throw Exception::GLTFException("GLTFObject is not a matrix");
  }
  for (int i = 0; i < mValue.size(); i += size) {
    Vec<Float> row;
    for (int j = 0; j < size; ++j) {
      row.push_back(mValue[i + j]);
    }
    result.push_back(row);
  }
  return result;
}

GLTFObject &GLTFObject::operator=(GLTFObject const &other) {
  mType = other.mType;
  mValue = other.mValue;
  return *this;
}

GLTFObject &GLTFObject::operator=(Vec<Float> const &value) {
  mType = GLTFType::SCALAR;
  mValue = value;
  return *this;
}

GLTFObject &GLTFObject::operator=(Vec<vec2> const &value) {
  mType = GLTFType::VEC2;
  mValue.clear();
  for (auto &v : value) {
    mValue.push_back(v.x);
    mValue.push_back(v.y);
  }
  return *this;
}

GLTFObject &GLTFObject::operator=(Vec<vec3> const &value) {
  mType = GLTFType::VEC3;
  mValue.clear();
  for (auto &v : value) {
    mValue.push_back(v.x);
    mValue.push_back(v.y);
    mValue.push_back(v.z);
  }
  return *this;
}

GLTFObject &GLTFObject::operator=(Vec<vec4> const &value) {
  mType = GLTFType::VEC4;
  mValue.clear();
  for (auto &v : value) {
    mValue.push_back(v.x);
    mValue.push_back(v.y);
    mValue.push_back(v.z);
    mValue.push_back(v.w);
  }
  return *this;
}

GLTFObject &GLTFObject::operator=(Vec<mat2> const &value) {
  mType = GLTFType::MAT2;
  mValue.clear();
  for (auto &m : value) {
    mValue.push_back(m[0][0]);
    mValue.push_back(m[0][1]);
    mValue.push_back(m[1][0]);
    mValue.push_back(m[1][1]);
  }
  return *this;
}

GLTFObject &GLTFObject::operator=(Vec<mat3> const &value) {
  mType = GLTFType::MAT3;
  mValue.clear();
  for (auto &m : value) {
    mValue.push_back(m[0][0]);
    mValue.push_back(m[0][1]);
    mValue.push_back(m[0][2]);
    mValue.push_back(m[1][0]);
    mValue.push_back(m[1][1]);
    mValue.push_back(m[1][2]);
    mValue.push_back(m[2][0]);
    mValue.push_back(m[2][1]);
    mValue.push_back(m[2][2]);
  }
  return *this;
}

GLTFObject &GLTFObject::operator=(Vec<mat4> const &value) {
  mType = GLTFType::MAT4;
  mValue.clear();
  for (auto &m : value) {
    mValue.push_back(m[0][0]);
    mValue.push_back(m[0][1]);
    mValue.push_back(m[0][2]);
    mValue.push_back(m[0][3]);
    mValue.push_back(m[1][0]);
    mValue.push_back(m[1][1]);
    mValue.push_back(m[1][2]);
    mValue.push_back(m[1][3]);
    mValue.push_back(m[2][0]);
    mValue.push_back(m[2][1]);
    mValue.push_back(m[2][2]);
    mValue.push_back(m[2][3]);
    mValue.push_back(m[3][0]);
    mValue.push_back(m[3][1]);
    mValue.push_back(m[3][2]);
    mValue.push_back(m[3][3]);
  }
  return *this;
}

Bool GLTFParser::LoadJson(ReadBuffer &buffer) {
  JSONParser parser;
  if (!parser.Parse(buffer)) {
    return false;
  }
  mJsonData = parser.GetRoot();

  if (!mJsonData.IsObject()) {
    return false;
  }
  return true;
}

Bool GLTFParser::ParseExtensions(JSON const &json) {
  JsonUtil::Extract(json, "extensionsUsed", mRoot.extensionsUsed);
  JsonUtil::Extract(json, "extensionsRequired", mRoot.extensionsRequired);
  return true;
}

Bool GLTFParser::ParseAccessors(JSON const &json,
                                Vec<GLTFAccessor> &container) {
  Array accessors;
  Bool status = JsonUtil::Extract(json, "accessors", accessors);
  if (!status) {
    return false;
  }

  for (auto &accessor : accessors) {
    GLTFAccessor acc;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - componentType
    // - count
    // - type
    /////////////////////////////////////////////////////////////////////////
    Utils::EnumConverter<GLTFType> typeConverter = [](Str const &src,
                                                      GLTFType &value) {
      value = Utils::ToGLTFType(src);
      return true;
    };
    Bool required =
        JsonUtil::Extract(accessor, "componentType", acc.componentType);
    required = required && JsonUtil::Extract(accessor, "count", acc.count);
    required =
        required && Utils::Extract(accessor, "type", acc.type, typeConverter);
    if (!required) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    JsonUtil::Extract(accessor, "bufferView", acc.bufferView);
    JsonUtil::Extract(accessor, "byteOffset", acc.byteOffset);
    JsonUtil::Extract(accessor, "normalized", acc.normalized);
    JsonUtil::Extract(accessor, "max", acc.max);
    JsonUtil::Extract(accessor, "min", acc.min);
    JsonUtil::Extract(accessor, "name", acc.name);

    container.push_back(acc);
  }

  return true;
}

Bool GLTFParser::ParseAnimationTarget(JSON const &json,
                                      GLTFAnimationTarget &container) {
  JSON target;
  Bool status = JsonUtil::Extract(json, "target", target);
  if (!status) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - path
  /////////////////////////////////////////////////////////////////////////
  if (!JsonUtil::Extract(target, "path", container.path)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  JsonUtil::Extract(target, "node", container.node);

  return true;
}

Bool GLTFParser::ParseAnimationChannels(JSON const &json,
                                        Vec<GLTFAnimationChannel> &container) {
  Array channels;
  Bool status = JsonUtil::Extract(json, "channels", channels);
  if (!status) {
    return false;
  }

  for (auto &channel : channels) {
    GLTFAnimationChannel chan;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - sampler
    // - target
    /////////////////////////////////////////////////////////////////////////
    if (!JsonUtil::Extract(channel, "sampler", chan.sampler) ||
        !this->ParseAnimationTarget(channel, chan.target)) {
      return false;
    }

    container.push_back(chan);
  }

  return true;
}

Bool GLTFParser::ParseAnimationSamplers(JSON const &json,
                                        Vec<GLTFAnimationSampler> &container) {
  Array samplers;
  Bool status = JsonUtil::Extract(json, "samplers", samplers);
  if (!status) {
    return false;
  }

  for (auto &sampler : samplers) {
    GLTFAnimationSampler samp;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - input
    // - output
    /////////////////////////////////////////////////////////////////////////
    Bool required = JsonUtil::Extract(sampler, "input", samp.input);
    required = required && JsonUtil::Extract(sampler, "output", samp.output);
    if (!required) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Utils::EnumConverter<GLTFInterpolationType> interpolationConverter =
        [](Str const &src, GLTFInterpolationType &value) {
          value = Utils::ToGLTFInterpolationType(src);
          return true;
        };
    Utils::Extract(sampler, "interpolation", samp.interpolation,
                   interpolationConverter);

    container.push_back(samp);
  }

  return true;
}

Bool GLTFParser::ParseAnimations(JSON const &json,
                                 Vec<GLTFAnimation> &container) {
  Array animations;
  Bool status = JsonUtil::Extract(json, "animations", animations);
  if (!status) {
    return true;
  }

  for (auto &animation : animations) {
    GLTFAnimation anim;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - channels
    // - samplers
    /////////////////////////////////////////////////////////////////////////
    if (!this->ParseAnimationChannels(animation, anim.channels)) {
      return false;
    }

    if (!this->ParseAnimationSamplers(animation, anim.samplers)) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    JsonUtil::Extract(animation, "name", anim.name);

    container.push_back(anim);
  }

  return true;
}

Bool GLTFParser::ParseAsset(JSON const &json, GLTFAsset &container) {
  JSON asset;
  Bool status = JsonUtil::Extract(json, "asset", asset);
  if (!status) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - version
  /////////////////////////////////////////////////////////////////////////
  if (!JsonUtil::Extract(asset, "version", container.version)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  JsonUtil::Extract(asset, "copyright", container.copyright);
  JsonUtil::Extract(asset, "generator", container.generator);
  JsonUtil::Extract(asset, "minVersion", container.minVersion);

  return true;
}

Bool GLTFParser::LoadBuffer(GLTFBuffer &buffer) {
  if (buffer.uri.empty()) {
    buffer.data = ReadBuffer(buffer.byteLength);
    return true;
  }

  ReadBuffer uri(buffer.uri);
  if (uri.Read(5) == "data:") {
    // Internal buffer mode
    // data:[<mediatype>];[encoding],<data>
    Str mediaType;
    while (uri.Fetch() != ';') {
      mediaType += uri.Read();
    }
    uri.Skip(); // Skip ';'

    if (mediaType != "application/octet-stream" &&
        mediaType != "application/gltf-buffer") {
      return false;
    }

    Str encoding;
    while (uri.Fetch() != ',') {
      encoding += uri.Read();
    }
    uri.Skip(); // Skip ','

    if (encoding != "base64") {
      return false;
    }

    buffer.data = BASE64::Decode(uri);
  } else {
    // External buffer mode
    // uri
    Str path = mParent + "/" + buffer.uri;
    buffer.data = ParserBase::LoadFile(path);
  }

  return true;
}

Bool GLTFParser::ParseBuffers(JSON const &json, Vec<GLTFBuffer> &container) {
  Array buffers;
  Bool status = JsonUtil::Extract(json, "buffers", buffers);
  if (!status) {
    return true;
  }

  for (auto &buffer : buffers) {
    GLTFBuffer buf;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - byteLength
    /////////////////////////////////////////////////////////////////////////
    if (!JsonUtil::Extract(buffer, "byteLength", buf.byteLength)) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    JsonUtil::Extract(buffer, "uri", buf.uri);
    JsonUtil::Extract(buffer, "name", buf.name);

    if (!this->LoadBuffer(buf)) {
      return false;
    }

    container.push_back(buf);
  }

  return true;
}

Bool GLTFParser::ParseBufferViews(JSON const &json,
                                  Vec<GLTFBufferView> &container) {
  Array bufferViews;
  Bool status = JsonUtil::Extract(json, "bufferViews", bufferViews);
  if (!status) {
    return true;
  }

  for (auto &bufferView : bufferViews) {
    GLTFBufferView bfrView;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - buffer
    // - byteLength
    /////////////////////////////////////////////////////////////////////////
    Bool required = JsonUtil::Extract(bufferView, "buffer", bfrView.buffer);
    required = required &&
               JsonUtil::Extract(bufferView, "byteLength", bfrView.byteLength);

    if (!required) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    JsonUtil::Extract(bufferView, "byteOffset", bfrView.byteOffset);
    JsonUtil::Extract(bufferView, "byteStride", bfrView.byteStride);
    JsonUtil::Extract(bufferView, "target", bfrView.target);
    JsonUtil::Extract(bufferView, "name", bfrView.name);

    container.push_back(bfrView);
  }

  return true;
}

Bool GLTFParser::ParseOrthographic(JSON const &json,
                                   GLTFOrthographic &container) {
  JSON orthographic;
  Bool status = JsonUtil::Extract(json, "orthographic", orthographic);
  if (!status) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - xmag
  // - ymag
  // - zfar
  // - znear
  /////////////////////////////////////////////////////////////////////////
  Bool required = JsonUtil::Extract(orthographic, "xmag", container.xmag);
  required =
      required && JsonUtil::Extract(orthographic, "ymag", container.ymag);
  required =
      required && JsonUtil::Extract(orthographic, "zfar", container.zfar);
  required =
      required && JsonUtil::Extract(orthographic, "znear", container.znear);

  if (!required) {
    return false;
  }

  return true;
}

Bool GLTFParser::ParsePerspective(JSON const &json,
                                  GLTFPerspective &container) {
  JSON perspective;
  Bool status = JsonUtil::Extract(json, "perspective", perspective);
  if (!status) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - yfov
  // - znear
  /////////////////////////////////////////////////////////////////////////
  Bool required = JsonUtil::Extract(perspective, "yfov", container.yfov);
  required =
      required && JsonUtil::Extract(perspective, "znear", container.znear);

  if (!required) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  JsonUtil::Extract(perspective, "aspectRatio", container.aspectRatio);
  JsonUtil::Extract(perspective, "zfar", container.zfar);

  return true;
}

Bool GLTFParser::ParseCameras(JSON const &json, Vec<GLTFCamera> &container) {
  Array cameras;
  Bool status = JsonUtil::Extract(json, "cameras", cameras);
  if (!status) {
    return true;
  }

  for (auto &camera : cameras) {
    GLTFCamera cam;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - type
    // - orthographic or perspective
    /////////////////////////////////////////////////////////////////////////
    Utils::EnumConverter<GLTFCameraType> typeConverter =
        [](Str const &src, GLTFCameraType &value) {
          value = Utils::ToGLTFCameraType(src);
          return true;
        };
    if (!Utils::Extract(camera, "type", cam.type, typeConverter)) {
      return false;
    }

    switch (cam.type) {
    case GLTFCameraType::ORTHOGRAPHIC:
      if (!this->ParseOrthographic(camera, cam.orthographic)) {
        return false;
      }
      break;
    case GLTFCameraType::PERSPECTIVE:
      if (!this->ParsePerspective(camera, cam.perspective)) {
        return false;
      }
      break;
    default:
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    JsonUtil::Extract(camera, "name", cam.name);

    container.push_back(cam);
  }

  return true;
}

Bool GLTFParser::ParseImages(JSON const &json, Vec<GLTFImage> &container) {
  Array images;
  Bool status = JsonUtil::Extract(json, "images", images);
  if (!status) {
    return true;
  }

  for (auto &image : images) {
    GLTFImage img;

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Utils::EnumConverter<GLTFMimeType> mimeTypeConverter =
        [](Str const &src, GLTFMimeType &value) {
          if (src == "image/jpeg") {
            value = GLTFMimeType::JPEG;
          } else if (src == "image/png") {
            value = GLTFMimeType::PNG;
          } else {
            return false;
          }
          return true;
        };
    JsonUtil::Extract(image, "uri", img.uri);
    JsonUtil::Extract(image, "bufferView", img.bufferView);
    Utils::Extract(image, "mimeType", img.mimeType, mimeTypeConverter);
    JsonUtil::Extract(image, "name", img.name);

    if (img.uri.empty() && !img.bufferView.Valid()) {
      return false;
    }

    if (img.uri.empty()) {
      GLTFBufferView &bufferView = mRoot.bufferViews[img.bufferView];
      auto &data = mRoot.buffers[bufferView.buffer].data;
      Int width, height, channels;
      Ubyte *ptr =
          stbi_load_from_memory((unsigned char *)data.GetBuffer(),
                                data.GetSize(), &width, &height, &channels, 4);
      if (ptr == nullptr) {
        return false;
      }

      img.texture = Texture(ptr, width, height, channels);
    } else {
      Int width, height, channels;
      Str path = mParent + "/" + img.uri;
      Ubyte *ptr = stbi_load(path.c_str(), &width, &height, &channels, 4);
      if (ptr == nullptr) {
        return false;
      }

      img.texture = Texture(ptr, width, height, channels);
    }

    container.push_back(img);
  }

  return true;
}

Bool GLTFParser::ParseTextureInfo(JSON const &json,
                                  GLTFTextureInfo &container) {
  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - index
  /////////////////////////////////////////////////////////////////////////
  if (!JsonUtil::Extract(json, "index", container.index)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  JsonUtil::Extract(json, "texCoord", container.texCoord);

  return true;
}

Bool GLTFParser::ParseTextureInfo(JSON const &json,
                                  Nullable<GLTFTextureInfo> &container) {
  if (!container.Valid()) {
    container = GLTFTextureInfo();
  }
  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - index
  /////////////////////////////////////////////////////////////////////////
  if (!JsonUtil::Extract(json, "index", container->index)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  JsonUtil::Extract(json, "texCoord", container->texCoord);

  return true;
}

Bool GLTFParser::ParsePBRMetallicRoughness(
    JSON const &json, GLTFPBRMetallicRoughness &container) {
  JSON pbrMR;
  Bool status = JsonUtil::Extract(json, "pbrMetallicRoughness", pbrMR);
  if (!status) {
    return true;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Vec<Float> baseColorFactor = {};
  JsonUtil::Extract(pbrMR, "baseColorFactor", baseColorFactor);
  JSON baseColorTexture;
  if (JsonUtil::Extract(pbrMR, "baseColorTexture", baseColorTexture)) {
    this->ParseTextureInfo(baseColorTexture, container.baseColorTexture);
  }
  JsonUtil::Extract(pbrMR, "metallicFactor", container.metallicFactor);
  JsonUtil::Extract(pbrMR, "roughnessFactor", container.roughnessFactor);
  JSON metallicRoughnessTexture;
  if (JsonUtil::Extract(pbrMR, "metallicRoughnessTexture",
                        metallicRoughnessTexture)) {
    this->ParseTextureInfo(metallicRoughnessTexture,
                           container.metallicRoughnessTexture);
  }

  if (baseColorFactor.size() == 4) {
    container.baseColorFactor = vec4(baseColorFactor[0], baseColorFactor[1],
                                     baseColorFactor[2], baseColorFactor[3]);
  }

  return true;
}

Bool GLTFParser::ParsePBRMetallicRoughness(
    JSON const &json, Nullable<GLTFPBRMetallicRoughness> &container) {
  JSON pbrMR;
  Bool status = JsonUtil::Extract(json, "pbrMetallicRoughness", pbrMR);
  if (!status) {
    return true;
  }

  if (!container.Valid()) {
    container = GLTFPBRMetallicRoughness();
  }
  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Vec<Float> baseColorFactor = {};
  JSON baseColorTexture;
  if (JsonUtil::Extract(pbrMR, "baseColorTexture", baseColorTexture)) {
    this->ParseTextureInfo(baseColorTexture, container->baseColorTexture);
  }
  JsonUtil::Extract(pbrMR, "metallicFactor", container->metallicFactor);
  JsonUtil::Extract(pbrMR, "roughnessFactor", container->roughnessFactor);
  JSON metallicRoughnessTexture;
  if (JsonUtil::Extract(pbrMR, "metallicRoughnessTexture",
                        metallicRoughnessTexture)) {
    this->ParseTextureInfo(metallicRoughnessTexture,
                           container->metallicRoughnessTexture);
  }

  if (baseColorFactor.size() == 4) {
    container->baseColorFactor = vec4(baseColorFactor[0], baseColorFactor[1],
                                      baseColorFactor[2], baseColorFactor[3]);
  }

  return true;
}

Bool GLTFParser::ParseNormalTextureInfo(JSON const &json,
                                        GLTFNormalTextureInfo &container) {
  JSON normalTexture;
  Bool status = JsonUtil::Extract(json, "normalTexture", normalTexture);
  if (!status) {
    return true;
  }

  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - index
  /////////////////////////////////////////////////////////////////////////
  if (!JsonUtil::Extract(normalTexture, "index", container.index)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  JsonUtil::Extract(normalTexture, "texCoord", container.texCoord);

  return true;
}

Bool GLTFParser::ParseNormalTextureInfo(
    JSON const &json, Nullable<GLTFNormalTextureInfo> &container) {
  JSON normalTexture;
  Bool status = JsonUtil::Extract(json, "normalTexture", normalTexture);
  if (!status) {
    return true;
  }

  if (!container.Valid()) {
    container = GLTFNormalTextureInfo();
  }
  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - index
  /////////////////////////////////////////////////////////////////////////
  if (!JsonUtil::Extract(json, "index", container->index)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  JsonUtil::Extract(json, "texCoord", container->texCoord);

  return true;
}

Bool GLTFParser::ParseOcclusionTextureInfo(
    JSON const &json, GLTFOcclusionTextureInfo &container) {
  JSON occlusionTexture;
  Bool status = JsonUtil::Extract(json, "occlusionTexture", occlusionTexture);
  if (!status) {
    return true;
  }

  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - index
  /////////////////////////////////////////////////////////////////////////
  if (!JsonUtil::Extract(occlusionTexture, "index", container.index)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  JsonUtil::Extract(occlusionTexture, "texCoord", container.texCoord);
  JsonUtil::Extract(occlusionTexture, "strength", container.strength);

  return true;
}

Bool GLTFParser::ParseOcclusionTextureInfo(
    JSON const &json, Nullable<GLTFOcclusionTextureInfo> &container) {
  JSON occlusionTexture;
  Bool status = JsonUtil::Extract(json, "occlusionTexture", occlusionTexture);
  if (!status) {
    return true;
  }

  if (!container.Valid()) {
    container = GLTFOcclusionTextureInfo();
  }
  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - index
  /////////////////////////////////////////////////////////////////////////
  if (!JsonUtil::Extract(json, "index", container->index)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  JsonUtil::Extract(json, "texCoord", container->texCoord);
  JsonUtil::Extract(json, "strength", container->strength);

  return true;
}

Bool GLTFParser::ParseMaterials(JSON const &json,
                                Vec<GLTFMaterial> &container) {
  Array materials;
  Bool status = JsonUtil::Extract(json, "materials", materials);
  if (!status) {
    return true;
  }

  for (auto &material : materials) {
    GLTFMaterial mat;

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Vec<Float> emissiveFactor = {};
    Utils::EnumConverter<GLTFAlphaMode> alphaModeConverter =
        [](Str const &src, GLTFAlphaMode &value) {
          value = Utils::ToGLTFAlphaMode(src);
          return true;
        };
    this->ParsePBRMetallicRoughness(material, mat.pbrMetallicRoughness);
    this->ParseNormalTextureInfo(material, mat.normalTexture);
    this->ParseOcclusionTextureInfo(material, mat.occlusionTexture);

    JSON emissiveTexture;
    if (JsonUtil::Extract(material, "emissiveTexture", emissiveTexture)) {
      this->ParseTextureInfo(emissiveTexture, mat.emissiveTexture);
    }
    JsonUtil::Extract(material, "emissiveFactor", emissiveFactor);
    Utils::Extract(material, "alphaMode", mat.alphaMode, alphaModeConverter);
    JsonUtil::Extract(material, "alphaCutoff", mat.alphaCutoff);
    JsonUtil::Extract(material, "doubleSided", mat.doubleSided);

    if (emissiveFactor.size() == 3) {
      mat.emissiveFactor =
          vec3(emissiveFactor[0], emissiveFactor[1], emissiveFactor[2]);
    }

    container.push_back(mat);
  }

  return true;
}

Bool GLTFParser::ParsePrimitives(JSON const &json,
                                 Vec<GLTFPrimitive> &container) {
  Array primitives;
  Bool status = JsonUtil::Extract(json, "primitives", primitives);
  if (!status) {
    return false;
  }

  for (auto &primitive : primitives) {
    GLTFPrimitive prim;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - attributes
    /////////////////////////////////////////////////////////////////////////
    if (!JsonUtil::Extract(primitive, "attributes", prim.attributes)) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    JsonUtil::Extract(primitive, "mode", prim.mode);
    JsonUtil::Extract(primitive, "indices", prim.indices);
    JsonUtil::Extract(primitive, "material", prim.material);

    Array morphTargets;
    JsonUtil::Extract(primitive, "targets", morphTargets);
    for (auto morphTarget : morphTargets) {
      Map<Str, Uint> target;
      for (auto &key : morphTarget.GetKeys()) {
        Uint value;
        if (!JsonUtil::Extract(morphTarget, key, value)) {
          return false;
        }
        target[key] = value;
      }
      prim.targets.push_back(target);
    }

    container.push_back(prim);
  }

  return true;
}

Bool GLTFParser::ParseMeshes(JSON const &json, Vec<GLTFMesh> &container) {
  Array meshes;
  Bool status = JsonUtil::Extract(json, "meshes", meshes);
  if (!status) {
    return true;
  }

  for (auto &mesh : meshes) {
    GLTFMesh msh;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - primitives
    /////////////////////////////////////////////////////////////////////////
    if (!this->ParsePrimitives(mesh, msh.primitives)) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    JsonUtil::Extract(mesh, "weights", msh.weights);
    JsonUtil::Extract(mesh, "name", msh.name);

    container.push_back(msh);
  }

  return true;
}

Bool GLTFParser::ParseNodes(JSON const &json, Vec<GLTFNode> &container) {
  Array nodes;
  Bool status = JsonUtil::Extract(json, "nodes", nodes);
  if (!status) {
    return true;
  }

  for (auto &node : nodes) {
    GLTFNode nd;

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Vec<Float> matrix = {};
    Vec<Float> rotation = {};
    Vec<Float> scale = {};
    Vec<Float> translation = {};
    JsonUtil::Extract(node, "camera", nd.camera);
    JsonUtil::Extract(node, "children", nd.children);
    JsonUtil::Extract(node, "skin", nd.skin);
    JsonUtil::Extract(node, "matrix", matrix);
    JsonUtil::Extract(node, "mesh", nd.mesh);
    JsonUtil::Extract(node, "rotation", rotation);
    JsonUtil::Extract(node, "scale", scale);
    JsonUtil::Extract(node, "translation", translation);
    JsonUtil::Extract(node, "weights", nd.weights);
    JsonUtil::Extract(node, "name", nd.name);

    if (matrix.size() == 16) {
      for (int i = 0; i < 16; ++i) {
        nd.matrix[i % 4][i / 4] = matrix[i];
      }
    }

    if (rotation.size() == 4) {
      nd.rotation = quat(rotation[3], rotation[0], rotation[1], rotation[2]);
    }

    if (scale.size() == 3) {
      nd.scale = vec3(scale[0], scale[1], scale[2]);
    }

    if (translation.size() == 3) {
      nd.translation = vec3(translation[0], translation[1], translation[2]);
    }

    container.push_back(nd);
  }

  return true;
}

Bool GLTFParser::ParseSamplers(JSON const &json, Vec<GLTFSampler> &container) {
  Array samplers;
  Bool status = JsonUtil::Extract(json, "samplers", samplers);
  if (!status) {
    return true;
  }

  for (auto &sampler : samplers) {
    GLTFSampler smp;

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    JsonUtil::Extract(sampler, "magFilter", smp.magFilter);
    JsonUtil::Extract(sampler, "minFilter", smp.minFilter);
    JsonUtil::Extract(sampler, "wrapS", smp.wrapS);
    JsonUtil::Extract(sampler, "wrapT", smp.wrapT);
    JsonUtil::Extract(sampler, "name", smp.name);

    container.push_back(smp);
  }

  return true;
}

Bool GLTFParser::ParseScenes(JSON const &json, Vec<GLTFScene> &container) {
  Array scenes;
  Bool status = JsonUtil::Extract(json, "scenes", scenes);
  if (!status) {
    return true;
  }

  for (auto &scene : scenes) {
    GLTFScene scn;

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    JsonUtil::Extract(scene, "nodes", scn.nodes);
    JsonUtil::Extract(scene, "name", scn.name);

    container.push_back(scn);
  }

  return true;
}

Bool GLTFParser::ParseSkins(JSON const &json, Vec<GLTFSkin> &container) {
  Array skins;
  Bool status = JsonUtil::Extract(json, "skins", skins);
  if (!status) {
    return true;
  }

  for (auto &skin : skins) {
    GLTFSkin sn;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - joints
    /////////////////////////////////////////////////////////////////////////
    if (!JsonUtil::Extract(skin, "joints", sn.joints)) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    JsonUtil::Extract(skin, "inverseBindMatrices", sn.inverseBindMatrices);
    JsonUtil::Extract(skin, "skeleton", sn.skeleton);
    JsonUtil::Extract(skin, "name", sn.name);

    container.push_back(sn);
  }

  return true;
}

Bool GLTFParser::ParseTextures(JSON const &json, Vec<GLTFTexture> &container) {
  Array textures;
  Bool status = JsonUtil::Extract(json, "textures", textures);
  if (!status) {
    return true;
  }

  for (auto &texture : textures) {
    GLTFTexture txt;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - source
    /////////////////////////////////////////////////////////////////////////
    if (!JsonUtil::Extract(texture, "source", txt.source)) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    JsonUtil::Extract(texture, "sampler", txt.sampler);
    JsonUtil::Extract(texture, "name", txt.name);

    container.push_back(txt);
  }

  return true;
}

Str GLTFParser::GetGLTFInfo() const {
  Str info = "GLTF Info\n";
  info += "Version: " + mRoot.asset.version + "\n";
  info += "Min Version: " + mRoot.asset.minVersion + "\n";
  info += "Generator: " + mRoot.asset.generator + "\n";
  info += "Copy Right: " + mRoot.asset.copyright + "\n";
  return info;
}

Bool GLTFParser::Parse(ReadBuffer &buffer) {
  Bool status = true;
  status = status && this->LoadJson(buffer);
  status = status && this->ParseExtensions(mJsonData);

  // Require: NONE
  status = status && this->ParseAsset(mJsonData, mRoot.asset);
  status = status && this->ParseCameras(mJsonData, mRoot.cameras);
  status = status && this->ParseSamplers(mJsonData, mRoot.samplers);
  status = status && this->ParseBuffers(mJsonData, mRoot.buffers);

  // Require: buffer
  status = status && this->ParseBufferViews(mJsonData, mRoot.bufferViews);

  // Require: bufferView
  status = status && this->ParseImages(mJsonData, mRoot.images);
  status = status && this->ParseAccessors(mJsonData, mRoot.accessors);

  // Require: image, sampler
  status = status && this->ParseTextures(mJsonData, mRoot.textures);

  // Require: texture
  status = status && this->ParseMaterials(mJsonData, mRoot.materials);

  // Require: accessor
  status = status && this->ParseAnimations(mJsonData, mRoot.animations);
  status = status && this->ParseSkins(mJsonData, mRoot.skins);

  // Require: accessor, material
  status = status && this->ParseMeshes(mJsonData, mRoot.meshes);

  // Require: mesh, camera
  status = status && this->ParseNodes(mJsonData, mRoot.nodes);

  // Require: node
  status = status && this->ParseScenes(mJsonData, mRoot.scenes);
  return status;
}

Bool GLTFParser::Parse() {
  ReadBuffer buffer = ParserBase::LoadFile(mFilePath);
  return this->Parse(buffer);
}

GLTFObject GLTFImporter::ParseAccessor(GLTFAccessor const &accessor) {
  if (!accessor.bufferView.Valid()) {
    return GLTFObject();
  }
  GLTFBufferView const &view = mRoot.bufferViews[accessor.bufferView];
  GLTFComponentType compType = accessor.componentType;

  Uint skip = 0;

  Uint stride = 0;
  if (view.byteStride.Valid()) {
    stride = view.byteStride;
  }

  if (stride != 0) {
    skip = stride - Utils::GetGLTFComponentTypeSize(compType) * accessor.count;

    switch (accessor.type) {
    case GLTFType::MAT2:
      if (compType == GLTFComponentType::BYTE ||
          compType == GLTFComponentType::UNSIGNED_BYTE) {
        skip -= 4;
      }
      break;
    case GLTFType::MAT3:
      if (compType == GLTFComponentType::BYTE ||
          compType == GLTFComponentType::UNSIGNED_BYTE) {
        skip -= 3;
      } else if (compType == GLTFComponentType::SHORT ||
                 compType == GLTFComponentType::UNSIGNED_SHORT) {
        skip -= 6;
      }
      break;
    default:
      break;
    }
  }

  ReadBuffer &buffer = mRoot.buffers[view.buffer].data;

  Vec<Float> data;
  switch (accessor.type) {
  case GLTFType::SCALAR:
    for (int i = 0; i < accessor.count; ++i) {
      data.push_back(Utils::Extract(compType, buffer));
      buffer.Skip(skip);
    }
    break;
  case GLTFType::VEC2:
    for (int i = 0; i < accessor.count; ++i) {
      for (int j = 0; j < 2; ++j) {
        data.push_back(Utils::Extract(compType, buffer));
      }
      buffer.Skip(skip);
    }
    break;
  case GLTFType::VEC3:
    for (int i = 0; i < accessor.count; ++i) {
      for (int j = 0; j < 3; ++j) {
        data.push_back(Utils::Extract(compType, buffer));
      }
      buffer.Skip(skip);
    }
    break;
  case GLTFType::VEC4:
    for (int i = 0; i < accessor.count; ++i) {
      for (int j = 0; j < 4; ++j) {
        data.push_back(Utils::Extract(compType, buffer));
      }
      buffer.Skip(skip);
    }
    break;
  case GLTFType::MAT2:
    for (int i = 0; i < accessor.count; ++i) {
      for (int j = 0; j < 2; ++j) {
        data.push_back(Utils::Extract(compType, buffer));
        data.push_back(Utils::Extract(compType, buffer));
        if (compType == GLTFComponentType::BYTE ||
            compType == GLTFComponentType::UNSIGNED_BYTE) {
          buffer.Skip(2); // Skip padding
        }
      }
      buffer.Skip(skip);
    }
    break;
  case GLTFType::MAT3:
    for (int i = 0; i < accessor.count; ++i) {
      for (int j = 0; j < 3; ++j) {
        data.push_back(Utils::Extract(compType, buffer));
        data.push_back(Utils::Extract(compType, buffer));
        data.push_back(Utils::Extract(compType, buffer));
        if (compType == GLTFComponentType::BYTE ||
            compType == GLTFComponentType::UNSIGNED_BYTE) {
          buffer.Skip(1); // Skip padding
        } else if (compType == GLTFComponentType::SHORT ||
                   compType == GLTFComponentType::UNSIGNED_SHORT) {
          buffer.Skip(2); // Skip padding
        }
      }
      buffer.Skip(skip);
    }
    break;
  case GLTFType::MAT4:
    for (int i = 0; i < accessor.count; ++i) {
      for (int j = 0; j < 4; ++j) {
        data.push_back(Utils::Extract(compType, buffer));
        data.push_back(Utils::Extract(compType, buffer));
        data.push_back(Utils::Extract(compType, buffer));
        data.push_back(Utils::Extract(compType, buffer));
      }
      buffer.Skip(skip);
    }
    break;
  default:
    throw Exception::GLTFException("Invalid accessor type");
  }

  return GLTFObject(accessor.type, data);
}

Camera GLTFImporter::ParseCamera(GLTFCamera const &camera) {
  Camera result;
  switch (camera.type) {
  case GLTFCameraType::PERSPECTIVE:
    result.SetType(CameraType::PERSPECTIVE);
    result.SetFov(camera.perspective.yfov);
    result.SetNear(camera.perspective.znear);
    result.SetFar(camera.perspective.zfar);
    result.SetSize({1.0, 1.0 / camera.perspective.aspectRatio});
    break;
  case GLTFCameraType::ORTHOGRAPHIC:
    result.SetType(CameraType::ORTHOGRAPHIC);
    result.SetWidth(camera.orthographic.xmag);
    result.SetHeight(camera.orthographic.ymag);
    result.SetNear(camera.orthographic.znear);
    result.SetFar(camera.orthographic.zfar);
    break;
  default:
    throw Exception::GLTFException("Invalid camera type");
  }
  return result;
}

Texture GLTFImporter::ParseTexture(GLTFTexture const &texture) {
  Texture result;
  if (texture.sampler.Valid()) {
    GLTFSampler sampler = mRoot.samplers[texture.sampler];
    result.magFilter = (TextureFilter)sampler.magFilter;
    result.minFilter = (TextureFilter)sampler.minFilter;
    result.wrapS = (TextureWrapping)sampler.wrapS;
    result.wrapT = (TextureWrapping)sampler.wrapT;
  }

  auto image = mRoot.images[texture.source];

  return result;
}

Material GLTFImporter::ParseMaterial(GLTFMaterial const &material) {
  Material result;
  if (material.name.size() > 0) {
    result.SetMaterialName(material.name);
  } else {
    result.SetMaterialName(result.GetUUID().ToString() + "_material");
  }

  result.SetDoubleSide(material.doubleSided);
  result.SetAlphaMode((AlphaMode)material.alphaMode);
  result.SetConstant(MaterialConstant::ALPHA, material.alphaCutoff);
  vec3 const &factor = material.emissiveFactor;
  Color emissive(factor.r, factor.g, factor.b);
  result.SetColor(MaterialColor::EMISSION, emissive);

  if (material.pbrMetallicRoughness.Valid()) {
    GLTFPBRMetallicRoughness pbr = material.pbrMetallicRoughness;
    result.SetConstant(MaterialConstant::METALLIC, pbr.metallicFactor);
    result.SetConstant(MaterialConstant::ROUGHNESS, pbr.roughnessFactor);
    Color baseColor(pbr.baseColorFactor.r, pbr.baseColorFactor.g,
                    pbr.baseColorFactor.b);
    result.SetColor(MaterialColor::BASE, baseColor);

    if (pbr.baseColorTexture.Valid()) {
      auto baseColorTexture =
          this->ParseTexture(mRoot.textures[pbr.baseColorTexture->index]);
      result.SetTexture(MaterialTexture::BASE_COLOR, baseColorTexture);
      Str targetUV = "iUV";
      if (pbr.baseColorTexture->texCoord.Valid()) {
        targetUV += std::to_string(pbr.baseColorTexture->texCoord);
      } else {
        targetUV += "0";
      }
      result.AddUVBinding(MaterialTexture::BASE_COLOR, targetUV);
    }
    if (pbr.metallicRoughnessTexture.Valid()) {
      auto metallicRoughnessTexture = this->ParseTexture(
          mRoot.textures[pbr.metallicRoughnessTexture->index]);
      result.SetTexture(MaterialTexture::METALLIC_ROUGHNESS,
                        metallicRoughnessTexture);
      Str targetUV = "iUV";
      if (pbr.metallicRoughnessTexture->texCoord.Valid()) {
        targetUV += std::to_string(pbr.metallicRoughnessTexture->texCoord);
      } else {
        targetUV += "0";
      }
      result.AddUVBinding(MaterialTexture::METALLIC_ROUGHNESS, targetUV);
    }
  }

  if (material.normalTexture.Valid()) {
    GLTFNormalTextureInfo normal = *material.normalTexture;
    result.SetConstant(MaterialConstant::NORMAL_SCALE, normal.scale);
    auto normalTexture = this->ParseTexture(mRoot.textures[normal.index]);
    result.SetTexture(MaterialTexture::NORMAL, normalTexture);
    Str targetUV = "iUV";
    if (normal.texCoord.Valid()) {
      targetUV += std::to_string(normal.texCoord);
    } else {
      targetUV += "0";
    }
    result.AddUVBinding(MaterialTexture::NORMAL, targetUV);
  }

  if (material.occlusionTexture.Valid()) {
    GLTFOcclusionTextureInfo occlusion = *material.occlusionTexture;
    result.SetConstant(MaterialConstant::OCCLUSION_STRENGTH,
                       occlusion.strength);
    auto occlusionTexture = this->ParseTexture(mRoot.textures[occlusion.index]);
    result.SetTexture(MaterialTexture::OCCLUSION, occlusionTexture);
    Str targetUV = "iUV";
    if (occlusion.texCoord.Valid()) {
      targetUV += std::to_string(occlusion.texCoord);
    } else {
      targetUV += "0";
    }
    result.AddUVBinding(MaterialTexture::OCCLUSION, targetUV);
  }

  if (material.emissiveTexture.Valid()) {
    GLTFTextureInfo emissive = *material.emissiveTexture;
    auto emissiveTexture = this->ParseTexture(mRoot.textures[emissive.index]);
    result.SetTexture(MaterialTexture::EMISSION, emissiveTexture);
    Str targetUV = "iUV";
    if (emissive.texCoord.Valid()) {
      targetUV += std::to_string(emissive.texCoord);
    } else {
      targetUV += "0";
    }
    result.AddUVBinding(MaterialTexture::EMISSION, targetUV);
  }

  return result;
}

MeshGroup GLTFImporter::ParseMesh(GLTFMesh const &mesh) {
  MeshGroup result;
  if (mesh.name.size() > 0) {
    result.SetName(mesh.name);
  } else {
    result.SetName(result.GetUUID().ToString() + "_mesh");
  }

  Uint vertexCount = 0;
  for (auto &primitive : mesh.primitives) {
    Mesh subMesh;
    if (primitive.indices != -1) {
      GLTFObject buffer = mAccessors[primitive.indices];
      subMesh.SetFaceIndices({buffer.AsScalar<Uint>()});
    }

    for (auto &attr : primitive.attributes) {
      auto component = mAccessors[attr.second].AsMatrix();
      vertexCount = component.size();
      ReadBuffer name = attr.first;
      switch (name.Fetch()) {
      case 'P':
        subMesh.AddVertexDataComponent("iPosition", component);
        break;
      case 'N':
        subMesh.AddVertexDataComponent("iNormal", component);
        break;
      case 'C':
        subMesh.AddVertexDataComponent("iColor", component);
        break;
      case 'J':
        subMesh.AddVertexDataComponent("iJoints", component);
        break;
      case 'W':
        subMesh.AddVertexDataComponent("iWeights", component);
        break;
      case 'T':
        if (name.Fetch() == 'A') {
          subMesh.AddVertexDataComponent("iTangent", component);
        } else if (name.Read(8) == "TEXCOORD") {
          name.Skip(); // Skip '_'
          Str idx = name.ReadAll();
          Bool scale = false;
          for (auto &comp : component) {
            if (comp[0] < 0.0f || comp[1] < 0.0f) {
              scale = true;
              break;
            }
          }

          if (!scale) {
            subMesh.AddVertexDataComponent("iUV" + idx, component);
          } else {
            Vec<Vec<Float>> converted;
            Float u, v, w;
            for (auto &comp : component) {
              std::cout << comp[0] << " " << comp[1] << std::endl;
              u = (comp[0] + 1.0f) / 2.0f;
              v = (comp[1] + 1.0f) / 2.0f;
              w = 0.0f;
              converted.push_back({u, v, w});
            }
            subMesh.AddVertexDataComponent("iUV" + idx, converted);
          }
        }
        break;
      }
    }

    for (auto &target : primitive.targets) {
      for (auto &attribute : target) {
        if (attribute.first == "POSITION") {
          subMesh.AddPositionMorphTarget(mAccessors[attribute.second].AsVec3());
        } else if (attribute.first == "NORMAL") {
          subMesh.AddNormalMorphTarget(mAccessors[attribute.second].AsVec3());
        } else if (attribute.first == "TANGENT") {
          subMesh.AddTangentMorphTarget(mAccessors[attribute.second].AsVec3());
        }
      }
    }

    for (auto &weight : mesh.weights) {
      subMesh.AddMorphWeight(weight);
    }

    Vec<Vec<Uint>> vertexConstructionIndices;
    Uint numComponents = subMesh.GetVertexDataComponents().size();
    for (int i = 0; i < vertexCount; ++i) {
      vertexConstructionIndices.push_back(Vec<Uint>(numComponents, i));
    }
    subMesh.SetVertexConstructionIndices(vertexConstructionIndices);
    auto material = this->ParseMaterial(mRoot.materials[primitive.material]);
    subMesh.SetMaterial(mScene.GetMaterials().size());
    mScene.AddMaterial(material);

    result.AddMesh(subMesh);
  }

  return result;
}

void GLTFImporter::ParseNode(Stage &stage, GLTFNode const &node) {
  if (node.name.size() > 0) {
    stage.SetName(node.name);
  } else {
    stage.SetName(stage.GetUUID().ToString() + "_node");
  }

  if (node.camera.Valid()) {
    stage.AddCamera(this->ParseCamera(mRoot.cameras[node.camera]));
  }

  mat4 mat = node.matrix;
  mat = translate(mat, node.translation) * mat4_cast(node.rotation) *
        scale(mat, node.scale);
  stage.SetTransform(mat);

  if (node.mesh.Valid()) {
    MeshGroup mesh = this->ParseMesh(mRoot.meshes[node.mesh]);
    mScene.AddMesh(mesh);
    stage.AddMeshIndex(mScene.GetMeshes().size() - 1);
  }

  if (node.children.size() > 0) {
    for (auto &index : node.children) {
      Stage child;
      if (std::find(mSkeletonRoots.begin(), mSkeletonRoots.end(), index) !=
          mSkeletonRoots.end()) { // Skip skeleton roots
        continue;
      }

      this->ParseNode(child, mRoot.nodes[index]);
      stage.AddChild(child);
    }
  }
}

void GLTFImporter::ParseModel() {
  if (!mImported) {
    throw Exception::GLTFException("Model not imported");
  }

  for (auto &accessor : mRoot.accessors) {
    mAccessors.push_back(this->ParseAccessor(accessor));
  }

  for (auto &skin : mRoot.skins) {
    mSkeletonRoots.push_back(skin.skeleton);
  }

  for (auto &scene : mRoot.scenes) {
    Stage stage;
    for (auto &index : scene.nodes) {
      if (std::find(mSkeletonRoots.begin(), mSkeletonRoots.end(), index) !=
          mSkeletonRoots.end()) { // Skip skeleton roots
        continue;
      }

      this->ParseNode(stage, mRoot.nodes[index]);
    }
  }
}

void GLTFImporter::Import(Str const &path) {
  GLTFParser parser(path);
  if (!parser.Parse()) {
    throw Exception::GLTFException("Failed to parse GLTF file");
  }

  mRoot = parser.GetRoot();
  mImported = true;
  this->ParseModel();
}
} // namespace TerreateIO::GLTF
