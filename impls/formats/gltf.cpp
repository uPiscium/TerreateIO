#include "../../includes/formats/gltf.hpp"
#include "../../includes/exceptions.hpp"

#include <iostream>

namespace TerreateIO::GLTF {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;

namespace Utils {
Bool Extract(JSON const &json, Str const &key, JSON &value) {
  if (!json.IsObject()) {
    throw Exception::GLTFException("JSON is not an object");
  }

  if (!json.Has(key)) {
    return false;
  }

  value = json[key];
  return true;
}

Bool Extract(JSON const &json, Str const &key, Bool &value) {
  JSON val;
  if (!Extract(json, key, val)) {
    return false;
  }

  if (!val.IsBool()) {
    throw Exception::GLTFException("JSON value is not a boolean");
  }

  value = val.GetBool();
  return true;
}

Bool Extract(JSON const &json, Str const &key, Double &value) {
  JSON val;
  if (!Extract(json, key, val)) {
    return false;
  }

  if (!val.IsNumber()) {
    throw Exception::GLTFException("JSON value is not a number");
  }

  value = val.GetNumber();
  return true;
}

Bool Extract(JSON const &json, Str const &key, Str &value) {
  JSON val;
  if (!Extract(json, key, val)) {
    return false;
  }

  if (!val.IsString()) {
    throw Exception::GLTFException("JSON value is not a string");
  }

  value = val.GetString();
  return true;
}

Bool Extract(JSON const &json, Str const &key, Array &value) {
  JSON val;
  if (!Extract(json, key, val)) {
    return false;
  }

  if (!val.IsArray()) {
    throw Exception::GLTFException("JSON value is not an array");
  }

  value = val.GetArray();
  return true;
}

Bool Extract(JSON const &json, Str const &key, Object &value) {
  JSON val;
  if (!Extract(json, key, val)) {
    return false;
  }

  if (!val.IsObject()) {
    throw Exception::GLTFException("JSON value is not an object");
  }

  value = val.GetObject();
  return true;
}

Bool Extract(JSON const &json, Str const &key, Vec<Bool> &value) {
  Array arr;
  if (!Extract(json, key, arr)) {
    return false;
  }

  for (auto &elem : arr) {
    if (!elem.IsBool()) {
      throw Exception::GLTFException("JSON array element is not a boolean");
    }
    value.push_back(elem.GetBool());
  }

  return true;
}

Bool Extract(JSON const &json, Str const &key, Vec<Double> &value) {
  Array arr;
  if (!Extract(json, key, arr)) {
    return false;
  }

  for (auto &elem : arr) {
    if (!elem.IsNumber()) {
      throw Exception::GLTFException("JSON array element is not a number");
    }
    value.push_back(elem.GetNumber());
  }

  return true;
}

Bool Extract(JSON const &json, Str const &key, Vec<Str> &value) {
  Array arr;
  if (!Extract(json, key, arr)) {
    return false;
  }

  for (auto &elem : arr) {
    if (!elem.IsString()) {
      throw Exception::GLTFException("JSON array element is not a string");
    }
    value.push_back(elem.GetString());
  }

  return true;
}

Bool Extract(JSON const &json, Str const &key, Map<Str, Bool> &value) {
  Object obj;
  if (!Extract(json, key, obj)) {
    return false;
  }

  for (auto &pair : obj) {
    if (!pair.second.IsBool()) {
      throw Exception::GLTFException("JSON object value is not a boolean");
    }
    value.insert({pair.first, pair.second.GetBool()});
  }

  return true;
}

Bool Extract(JSON const &json, Str const &key, Map<Str, Double> &value) {
  Object obj;
  if (!Extract(json, key, obj)) {
    return false;
  }

  for (auto &pair : obj) {
    if (!pair.second.IsNumber()) {
      throw Exception::GLTFException("JSON object value is not a number");
    }
    value.insert({pair.first, pair.second.GetNumber()});
  }

  return true;
}

Bool Extract(JSON const &json, Str const &key, Map<Str, Str> &value) {
  Object obj;
  if (!Extract(json, key, obj)) {
    return false;
  }

  for (auto &pair : obj) {
    if (!pair.second.IsString()) {
      throw Exception::GLTFException("JSON object value is not a string");
    }
    value.insert({pair.first, pair.second.GetString()});
  }

  return true;
}

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
} // namespace Utils

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

Bool GLTFParser::ParseAccessors(JSON const &json,
                                Vec<GLTFAccessor> &container) {
  Array accessors;
  Bool status = Utils::Extract(json, "accessors", accessors);
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
        Utils::Extract(accessor, "componentType", acc.componentType);
    required = required && Utils::Extract(accessor, "count", acc.count);
    required =
        required && Utils::Extract(accessor, "type", acc.type, typeConverter);
    if (!required) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Utils::Extract(accessor, "bufferView", acc.bufferView);
    Utils::Extract(accessor, "byteOffset", acc.byteOffset);
    Utils::Extract(accessor, "normalized", acc.normalized);
    Utils::Extract(accessor, "max", acc.max);
    Utils::Extract(accessor, "min", acc.min);
    Utils::Extract(accessor, "name", acc.name);

    container.push_back(acc);
  }

  return true;
}

Bool GLTFParser::ParseAnimationTarget(JSON const &json,
                                      GLTFAnimationTarget &container) {
  JSON target;
  Bool status = Utils::Extract(json, "target", target);
  if (!status) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - path
  /////////////////////////////////////////////////////////////////////////
  if (!Utils::Extract(target, "path", container.path)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Utils::Extract(target, "node", container.node);

  return true;
}

Bool GLTFParser::ParseAnimationChannels(JSON const &json,
                                        Vec<GLTFAnimationChannel> &container) {
  Array channels;
  Bool status = Utils::Extract(json, "channels", channels);
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
    if (!Utils::Extract(channel, "sampler", chan.sampler) ||
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
  Bool status = Utils::Extract(json, "samplers", samplers);
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
    Bool required = Utils::Extract(sampler, "input", samp.input);
    required = required && Utils::Extract(sampler, "output", samp.output);
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
  Bool status = Utils::Extract(json, "animations", animations);
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
    Utils::Extract(animation, "name", anim.name);

    container.push_back(anim);
  }

  return true;
}

Bool GLTFParser::ParseAsset(JSON const &json, GLTFAsset &container) {
  JSON asset;
  Bool status = Utils::Extract(json, "asset", asset);
  if (!status) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - version
  /////////////////////////////////////////////////////////////////////////
  if (!Utils::Extract(asset, "version", container.version)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Utils::Extract(asset, "copyright", container.copyright);
  Utils::Extract(asset, "generator", container.generator);
  Utils::Extract(asset, "minVersion", container.minVersion);

  return true;
}

Bool GLTFParser::ParseBuffers(JSON const &json, Vec<GLTFBuffer> &container) {
  Array buffers;
  Bool status = Utils::Extract(json, "buffers", buffers);
  if (!status) {
    return true;
  }

  for (auto &buffer : buffers) {
    GLTFBuffer buf;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - byteLength
    /////////////////////////////////////////////////////////////////////////
    if (!Utils::Extract(buffer, "byteLength", buf.byteLength)) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Utils::Extract(buffer, "uri", buf.uri);
    Utils::Extract(buffer, "name", buf.name);

    container.push_back(buf);
  }

  return true;
}

Bool GLTFParser::ParseBufferViews(JSON const &json,
                                  Vec<GLTFBufferView> &container) {
  Array bufferViews;
  Bool status = Utils::Extract(json, "bufferViews", bufferViews);
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
    Bool required = Utils::Extract(bufferView, "buffer", bfrView.buffer);
    required = required &&
               Utils::Extract(bufferView, "byteLength", bfrView.byteLength);

    if (!required) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Utils::Extract(bufferView, "byteOffset", bfrView.byteOffset);
    Utils::Extract(bufferView, "byteStride", bfrView.byteStride);
    Utils::Extract(bufferView, "target", bfrView.target);
    Utils::Extract(bufferView, "name", bfrView.name);

    container.push_back(bfrView);
  }

  return true;
}

Bool GLTFParser::ParseOrthographic(JSON const &json,
                                   GLTFOrthographic &container) {
  JSON orthographic;
  Bool status = Utils::Extract(json, "orthographic", orthographic);
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
  Bool required = Utils::Extract(orthographic, "xmag", container.xmag);
  required = required && Utils::Extract(orthographic, "ymag", container.ymag);
  required = required && Utils::Extract(orthographic, "zfar", container.zfar);
  required = required && Utils::Extract(orthographic, "znear", container.znear);

  if (!required) {
    return false;
  }

  return true;
}

Bool GLTFParser::ParsePerspective(JSON const &json,
                                  GLTFPerspective &container) {
  JSON perspective;
  Bool status = Utils::Extract(json, "perspective", perspective);
  if (!status) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - yfov
  // - znear
  /////////////////////////////////////////////////////////////////////////
  Bool required = Utils::Extract(perspective, "yfov", container.yfov);
  required = required && Utils::Extract(perspective, "znear", container.znear);

  if (!required) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Utils::Extract(perspective, "aspectRatio", container.aspectRatio);
  Utils::Extract(perspective, "zfar", container.zfar);

  return true;
}

Bool GLTFParser::ParseCameras(JSON const &json, Vec<GLTFCamera> &container) {
  Array cameras;
  Bool status = Utils::Extract(json, "cameras", cameras);
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
    Utils::Extract(camera, "name", cam.name);

    container.push_back(cam);
  }

  return true;
}

Bool GLTFParser::ParseImages(JSON const &json, Vec<GLTFImage> &container) {
  Array images;
  Bool status = Utils::Extract(json, "images", images);
  if (!status) {
    return true;
  }

  for (auto &image : images) {
    GLTFImage img;

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Utils::Extract(image, "uri", img.uri);
    Utils::Extract(image, "bufferView", img.bufferView);
    Utils::Extract(image, "mimeType", img.mimeType);
    Utils::Extract(image, "name", img.name);

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
  if (!Utils::Extract(json, "index", container.index)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Utils::Extract(json, "texCoord", container.texCoord);

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
  if (!Utils::Extract(json, "index", container->index)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Utils::Extract(json, "texCoord", container->texCoord);

  return true;
}

Bool GLTFParser::ParsePBRMetallicRoughness(
    JSON const &json, GLTFPBRMetallicRoughness &container) {
  JSON pbrMR;
  Bool status = Utils::Extract(json, "pbrMetallicRoughness", pbrMR);
  if (!status) {
    return true;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Vec<Float> baseColorFactor = {};
  Utils::Extract(pbrMR, "baseColorFactor", baseColorFactor);
  JSON baseColorTexture;
  if (Utils::Extract(pbrMR, "baseColorTexture", baseColorTexture)) {
    this->ParseTextureInfo(baseColorTexture, container.baseColorTexture);
  }
  Utils::Extract(pbrMR, "metallicFactor", container.metallicFactor);
  Utils::Extract(pbrMR, "roughnessFactor", container.roughnessFactor);
  JSON metallicRoughnessTexture;
  if (Utils::Extract(pbrMR, "metallicRoughnessTexture",
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
  if (!container.Valid()) {
    container = GLTFPBRMetallicRoughness();
  }
  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Vec<Float> baseColorFactor = {};
  JSON baseColorTexture;
  if (Utils::Extract(json, "baseColorTexture", baseColorTexture)) {
    this->ParseTextureInfo(baseColorTexture, container->baseColorTexture);
  }
  Utils::Extract(json, "metallicFactor", container->metallicFactor);
  Utils::Extract(json, "roughnessFactor", container->roughnessFactor);
  JSON metallicRoughnessTexture;
  if (Utils::Extract(json, "metallicRoughnessTexture",
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
  Bool status = Utils::Extract(json, "normalTexture", normalTexture);
  if (!status) {
    return true;
  }

  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - index
  /////////////////////////////////////////////////////////////////////////
  if (!Utils::Extract(normalTexture, "index", container.index)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Utils::Extract(normalTexture, "texCoord", container.texCoord);

  return true;
}

Bool GLTFParser::ParseNormalTextureInfo(
    JSON const &json, Nullable<GLTFNormalTextureInfo> &container) {
  if (!container.Valid()) {
    container = GLTFNormalTextureInfo();
  }
  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - index
  /////////////////////////////////////////////////////////////////////////
  if (!Utils::Extract(json, "index", container->index)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Utils::Extract(json, "texCoord", container->texCoord);

  return true;
}

Bool GLTFParser::ParseOcclusionTextureInfo(
    JSON const &json, GLTFOcclusionTextureInfo &container) {
  JSON occlusionTexture;
  Bool status = Utils::Extract(json, "occlusionTexture", occlusionTexture);
  if (!status) {
    return true;
  }

  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - index
  /////////////////////////////////////////////////////////////////////////
  if (!Utils::Extract(occlusionTexture, "index", container.index)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Utils::Extract(occlusionTexture, "texCoord", container.texCoord);
  Utils::Extract(occlusionTexture, "strength", container.strength);

  return true;
}

Bool GLTFParser::ParseOcclusionTextureInfo(
    JSON const &json, Nullable<GLTFOcclusionTextureInfo> &container) {
  if (!container.Valid()) {
    container = GLTFOcclusionTextureInfo();
  }
  /////////////////////////////////////////////////////////////////////////
  // Required properties
  // - index
  /////////////////////////////////////////////////////////////////////////
  if (!Utils::Extract(json, "index", container->index)) {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  // Optional properties
  /////////////////////////////////////////////////////////////////////////
  Utils::Extract(json, "texCoord", container->texCoord);
  Utils::Extract(json, "strength", container->strength);

  return true;
}

Bool GLTFParser::ParseMaterials(JSON const &json,
                                Vec<GLTFMaterial> &container) {
  Array materials;
  Bool status = Utils::Extract(json, "materials", materials);
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
    this->ParseTextureInfo(material, mat.emissiveTexture);
    Utils::Extract(material, "emissiveFactor", emissiveFactor);
    Utils::Extract(material, "alphaMode", mat.alphaMode, alphaModeConverter);
    Utils::Extract(material, "alphaCutoff", mat.alphaCutoff);
    Utils::Extract(material, "doubleSided", mat.doubleSided);

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
  Bool status = Utils::Extract(json, "primitives", primitives);
  if (!status) {
    return false;
  }

  for (auto &primitive : primitives) {
    GLTFPrimitive prim;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - attributes
    /////////////////////////////////////////////////////////////////////////
    if (!Utils::Extract(primitive, "attributes", prim.attributes)) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Utils::Extract(primitive, "mode", prim.mode);
    Utils::Extract(primitive, "indices", prim.indices);
    Utils::Extract(primitive, "material", prim.material);
    Utils::Extract(primitive, "morphTargets", prim.morphTargets);

    container.push_back(prim);
  }

  return true;
}

Bool GLTFParser::ParseMeshes(JSON const &json, Vec<GLTFMesh> &container) {
  Array meshes;
  Bool status = Utils::Extract(json, "meshes", meshes);
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
    Utils::Extract(mesh, "weights", msh.weights);
    Utils::Extract(mesh, "name", msh.name);

    container.push_back(msh);
  }

  return true;
}

Bool GLTFParser::ParseNodes(JSON const &json, Vec<GLTFNode> &container) {
  Array nodes;
  Bool status = Utils::Extract(json, "nodes", nodes);
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
    Utils::Extract(node, "camera", nd.camera);
    Utils::Extract(node, "children", nd.children);
    Utils::Extract(node, "skin", nd.skin);
    Utils::Extract(node, "matrix", matrix);
    Utils::Extract(node, "mesh", nd.mesh);
    Utils::Extract(node, "rotation", rotation);
    Utils::Extract(node, "scale", scale);
    Utils::Extract(node, "translation", translation);
    Utils::Extract(node, "weights", nd.weights);
    Utils::Extract(node, "name", nd.name);

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
  Bool status = Utils::Extract(json, "samplers", samplers);
  if (!status) {
    return true;
  }

  for (auto &sampler : samplers) {
    GLTFSampler smp;

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Utils::Extract(sampler, "magFilter", smp.magFilter);
    Utils::Extract(sampler, "minFilter", smp.minFilter);
    Utils::Extract(sampler, "wrapS", smp.wrapS);
    Utils::Extract(sampler, "wrapT", smp.wrapT);
    Utils::Extract(sampler, "name", smp.name);

    container.push_back(smp);
  }

  return true;
}

Bool GLTFParser::ParseScenes(JSON const &json, Vec<GLTFScene> &container) {
  Array scenes;
  Bool status = Utils::Extract(json, "scenes", scenes);
  if (!status) {
    return true;
  }

  for (auto &scene : scenes) {
    GLTFScene scn;

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Utils::Extract(scene, "nodes", scn.nodes);
    Utils::Extract(scene, "name", scn.name);

    container.push_back(scn);
  }

  return true;
}

Bool GLTFParser::ParseSkins(JSON const &json, Vec<GLTFSkin> &container) {
  Array skins;
  Bool status = Utils::Extract(json, "skins", skins);
  if (!status) {
    return true;
  }

  for (auto &skin : skins) {
    GLTFSkin sn;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - joints
    /////////////////////////////////////////////////////////////////////////
    if (!Utils::Extract(skin, "joints", sn.joints)) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Utils::Extract(skin, "inverseBindMatrices", sn.inverseBindMatrices);
    Utils::Extract(skin, "skeleton", sn.skeleton);
    Utils::Extract(skin, "name", sn.name);

    container.push_back(sn);
  }

  return true;
}

Bool GLTFParser::ParseTextures(JSON const &json, Vec<GLTFTexture> &container) {
  Array textures;
  Bool status = Utils::Extract(json, "textures", textures);
  if (!status) {
    return true;
  }

  for (auto &texture : textures) {
    GLTFTexture txt;

    /////////////////////////////////////////////////////////////////////////
    // Required properties
    // - source
    /////////////////////////////////////////////////////////////////////////
    if (!Utils::Extract(texture, "source", txt.source)) {
      return false;
    }

    /////////////////////////////////////////////////////////////////////////
    // Optional properties
    /////////////////////////////////////////////////////////////////////////
    Utils::Extract(texture, "sampler", txt.sampler);
    Utils::Extract(texture, "name", txt.name);

    container.push_back(txt);
  }

  return true;
}

void GLTFParser::ParseBinary() {
  Vec<GLTFBuffer> buffers = mRoot.buffers;
  Vec<GLTFBufferView> bufferViews = mRoot.bufferViews;

  Vec<ReadBuffer> bufferStorages;
  for (auto &buffer : buffers) {
    if (buffer.uri.empty()) { // uri is optional
      continue;
    }

    ReadBuffer bufferStorage;

    ReadBuffer uri(buffer.uri);
    if (uri.Read(5) == "data:") {
      // Internal buffer mode
      // data:[<mediatype>];[encoding],<data>
      Str mediaType;
      while (uri.Peek() != ';') {
        mediaType += uri.Read();
      }
      uri.Skip(); // Skip ';'

      if (mediaType != "application/octet-stream" &&
          mediaType != "application/gltf-buffer") {
        throw Exception::GLTFException("Invalid media type");
      }

      Str encoding;
      while (uri.Peek() != ',') {
        encoding += uri.Read();
      }
      uri.Skip(); // Skip ','

      if (encoding != "base64") {
        throw Exception::GLTFException("Invalid encoding");
      }

      bufferStorage = uri;
    } else {
      // External buffer mode
      // uri
      Str path = mParent + "/" + buffer.uri;
      bufferStorage = ParserBase::LoadFile(path);
    }

    bufferStorages.push_back(bufferStorage);
  }

  struct BinaryBuffer {
    ReadBuffer buffer;
    Nullable<Uint> stride;
  };

  Vec<BinaryBuffer> binaryStorages;
  for (auto &bufferView : bufferViews) {
    BinaryBuffer binaryStorage;
    binaryStorage.buffer = bufferStorages[bufferView.buffer].Sub(
        bufferView.byteOffset, bufferView.byteLength);
    binaryStorage.stride = bufferView.byteStride;
  }

  Vec<GLTFAccessor> accessors = mRoot.accessors;
  for (auto &accessor : accessors) {
    if (!accessor.bufferView.Valid()) {
      continue;
    }

    BinaryBuffer binaryStorage = binaryStorages[*accessor.bufferView];
    ReadBuffer &buffer = binaryStorage.buffer;
    buffer.Skip(accessor.byteOffset);
  }
}

Handle GLTFParser::ParseGLTFMetadata() {
  Utils::Extract(mJsonData, "extensionsUsed", mRoot.extensionsUsed);
  Utils::Extract(mJsonData, "extensionsRequired", mRoot.extensionsRequired);

  Runnable accessors([this]() {
    Bool state = this->ParseAccessors(mJsonData, mRoot.accessors);
  });
  Runnable animations([this]() {
    Bool state = this->ParseAnimations(mJsonData, mRoot.animations);
  });
  Runnable asset(
      [this]() { Bool state = this->ParseAsset(mJsonData, mRoot.asset); });
  Runnable buffers(
      [this]() { Bool state = this->ParseBuffers(mJsonData, mRoot.buffers); });
  Runnable bufferViews([this]() {
    Bool state = this->ParseBufferViews(mJsonData, mRoot.bufferViews);
  });
  Runnable cameras(
      [this]() { Bool state = this->ParseCameras(mJsonData, mRoot.cameras); });
  Runnable images(
      [this]() { Bool state = this->ParseImages(mJsonData, mRoot.images); });
  Runnable materials([this]() {
    Bool state = this->ParseMaterials(mJsonData, mRoot.materials);
  });
  Runnable meshes(
      [this]() { Bool state = this->ParseMeshes(mJsonData, mRoot.meshes); });
  Runnable nodes(
      [this]() { Bool state = this->ParseNodes(mJsonData, mRoot.nodes); });
  Runnable samplers([this]() {
    Bool state = this->ParseSamplers(mJsonData, mRoot.samplers);
  });
  Runnable scenes(
      [this]() { Bool state = this->ParseScenes(mJsonData, mRoot.scenes); });
  Runnable skins(
      [this]() { Bool state = this->ParseSkins(mJsonData, mRoot.skins); });
  Runnable textures([this]() {
    Bool state = this->ParseTextures(mJsonData, mRoot.textures);
  });

  Vec<Handle> deps;
  deps.push_back(mExecutor.Schedule(accessors));
  deps.push_back(mExecutor.Schedule(animations));
  deps.push_back(mExecutor.Schedule(asset));
  deps.push_back(mExecutor.Schedule(buffers));
  deps.push_back(mExecutor.Schedule(bufferViews));
  deps.push_back(mExecutor.Schedule(cameras));
  deps.push_back(mExecutor.Schedule(images));
  deps.push_back(mExecutor.Schedule(materials));
  deps.push_back(mExecutor.Schedule(meshes));
  deps.push_back(mExecutor.Schedule(nodes));
  deps.push_back(mExecutor.Schedule(samplers));
  deps.push_back(mExecutor.Schedule(scenes));
  deps.push_back(mExecutor.Schedule(skins));
  deps.push_back(mExecutor.Schedule(textures));

  Runnable metadata([this]() {
    for (auto &pair : mParsingStatus) {
      if (!pair.second) {
        throw Exception::GLTFException("Failed to parse GLTF metadata");
      }
    }
  });
  return mExecutor.Schedule(metadata, deps);
}

Bool GLTFParser::Parse(ReadBuffer &buffer) {
  this->LoadJson(buffer);
  Handle metadataHandle = this->ParseGLTFMetadata();
  mExecutor.WaitForAll();

  std::cout << mExecutor.GetExceptions().size() << std::endl;

  return true;
}

Bool GLTFParser::Parse() {
  ReadBuffer buffer = ParserBase::LoadFile(mFilePath);
  return this->Parse(buffer);
}
} // namespace TerreateIO::GLTF
