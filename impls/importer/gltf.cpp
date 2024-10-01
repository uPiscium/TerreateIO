#include "../../includes/importer/gltf.hpp"
#include "../exceptions.hpp"

namespace TerreateIO::GLTF {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;
using namespace TerreateCore::Math;
using namespace TerreateIO::Container;

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

GLTFObject GLTFImporter::ParseAccessor(tinygltf::Accessor const &accessor) {
  Int stride = accessor.ByteStride(mModel.bufferViews[accessor.bufferView]);
  tinygltf::BufferView const &view = mModel.bufferViews[accessor.bufferView];
  tinygltf::Buffer const &buffer = mModel.buffers[view.buffer];

  GLTFType type;
  Vec<Float> data;
  Byte const *ptr = (Byte const *)(buffer.data.data() + view.byteOffset);
  switch (accessor.type) {
  case TINYGLTF_TYPE_SCALAR:
    type = GLTFType::SCALAR;
    for (int i = 0; i < accessor.count; ++i) {
      Float value = *(reinterpret_cast<Float const *>(ptr + stride * i));
      data.push_back(value);
    }
    break;
  case TINYGLTF_TYPE_VEC2:
    type = GLTFType::VEC2;
    for (int i = 0; i < accessor.count; ++i) {
      vec2 value = *(reinterpret_cast<vec2 const *>(ptr + stride * i));
      data.push_back(value.x);
      data.push_back(value.y);
    }
    break;
  case TINYGLTF_TYPE_VEC3:
    type = GLTFType::VEC3;
    for (int i = 0; i < accessor.count; ++i) {
      vec3 value = *(reinterpret_cast<vec3 const *>(ptr + stride * i));
      data.push_back(value.x);
      data.push_back(value.y);
      data.push_back(value.z);
    }
    break;
  case TINYGLTF_TYPE_VEC4:
    type = GLTFType::VEC4;
    for (int i = 0; i < accessor.count; ++i) {
      vec4 value = *(reinterpret_cast<vec4 const *>(ptr + stride * i));
      data.push_back(value.x);
      data.push_back(value.y);
      data.push_back(value.z);
      data.push_back(value.w);
    }
    break;
  case TINYGLTF_TYPE_MAT2:
    type = GLTFType::MAT2;
    for (int i = 0; i < accessor.count; ++i) {
      mat2 value = *(reinterpret_cast<mat2 const *>(ptr + stride * i));
      data.push_back(value[0][0]);
      data.push_back(value[0][1]);
      data.push_back(value[1][0]);
      data.push_back(value[1][1]);

      if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_BYTE ||
          accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) {
        ptr += 2; // Skip padding
      }
    }
    break;
  case TINYGLTF_TYPE_MAT3:
    type = GLTFType::MAT3;
    for (int i = 0; i < accessor.count; ++i) {
      mat3 value = *(reinterpret_cast<mat3 const *>(ptr + stride * i));
      data.push_back(value[0][0]);
      data.push_back(value[0][1]);
      data.push_back(value[0][2]);
      data.push_back(value[1][0]);
      data.push_back(value[1][1]);
      data.push_back(value[1][2]);
      data.push_back(value[2][0]);
      data.push_back(value[2][1]);
      data.push_back(value[2][2]);

      if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_BYTE ||
          accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) {
        ptr += 1; // Skip padding
      } else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_SHORT ||
                 accessor.componentType ==
                     TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
        ptr += 2; // Skip padding
      }
    }
    break;
  case TINYGLTF_TYPE_MAT4:
    type = GLTFType::MAT4;
    for (int i = 0; i < accessor.count; ++i) {
      mat4 value = *(reinterpret_cast<mat4 const *>(ptr + stride * i));
      data.push_back(value[0][0]);
      data.push_back(value[0][1]);
      data.push_back(value[0][2]);
      data.push_back(value[0][3]);
      data.push_back(value[1][0]);
      data.push_back(value[1][1]);
      data.push_back(value[1][2]);
      data.push_back(value[1][3]);
      data.push_back(value[2][0]);
      data.push_back(value[2][1]);
      data.push_back(value[2][2]);
      data.push_back(value[2][3]);
      data.push_back(value[3][0]);
      data.push_back(value[3][1]);
      data.push_back(value[3][2]);
      data.push_back(value[3][3]);
    }
    break;
  default:
    throw Exception::GLTFException("Invalid accessor type");
  }

  return GLTFObject(type, data);
}

Camera GLTFImporter::ParseCamera(tinygltf::Camera const &camera) {
  Camera result;
  if (camera.type == "perspective") {
    result.SetType(CameraType::PERSPECTIVE);
    result.SetFov(camera.perspective.yfov);
    result.SetNear(camera.perspective.znear);
    result.SetFar(camera.perspective.zfar);
    Double ratio = camera.perspective.aspectRatio;
    result.SetSize({1.0, 1.0 / ratio});
  } else if (camera.type == "orthographic") {
    result.SetType(CameraType::ORTHOGRAPHIC);
    result.SetWidth(camera.orthographic.xmag);
    result.SetHeight(camera.orthographic.ymag);
    result.SetNear(camera.orthographic.znear);
    result.SetFar(camera.orthographic.zfar);
  }
  return result;
}

Mesh GLTFImporter::ParseMesh(tinygltf::Mesh const &mesh) {
  Mesh result;
  for (auto &primitive : mesh.primitives) {
    if (primitive.indices != -1) {
      GLTFObject buffer = mAccessors[primitive.indices];
      result.SetFaceIndices({buffer.AsScalar<Uint>()});
    }

    for (auto &attr : primitive.attributes) {
      if (attr.first == "POSITION") {
        result.AddVertexDataComponent("iPosition",
                                      mAccessors[attr.second].AsMatrix());
      } else if (attr.first == "NORMAL") {
        result.AddVertexDataComponent("iNormal",
                                      mAccessors[attr.second].AsMatrix());
      } else if (attr.first == "TANGENT") {
        result.AddVertexDataComponent("iTangent",
                                      mAccessors[attr.second].AsMatrix());
      } else if (attr.first == "TEXCOORD_0") {
        result.AddVertexDataComponent("iTexCoord",
                                      mAccessors[attr.second].AsMatrix());
      } else if (attr.first == "COLOR_0") {
        result.AddVertexDataComponent("iColor",
                                      mAccessors[attr.second].AsMatrix());
      } else if (attr.first == "JOINTS_0") {
        result.AddVertexDataComponent("iJoints",
                                      mAccessors[attr.second].AsMatrix());
      } else if (attr.first == "WEIGHTS_0") {
        result.AddVertexDataComponent("iWeights",
                                      mAccessors[attr.second].AsMatrix());
      }
    }

    for (auto &target : primitive.targets) {
      for (auto &attribute : target) {
        if (attribute.first == "POSITION") {
          result.AddPositionMorphTarget(mAccessors[attribute.second].AsVec3());
        } else if (attribute.first == "NORMAL") {
          result.AddNormalMorphTarget(mAccessors[attribute.second].AsVec3());
        } else if (attribute.first == "TANGENT") {
          result.AddTangentMorphTarget(mAccessors[attribute.second].AsVec3());
        }
      }
    }
  }

  for (auto &weight : mesh.weights) {
    result.AddMorphWeight(weight);
  }

  return result;
}

void GLTFImporter::ParseNode(Stage &stage, tinygltf::Node const &node) {
  if (node.name.size() > 0) {
    stage.SetName(node.name);
  } else {
    stage.SetName(stage.GetUUID().ToString() + "_node");
  }

  if (node.camera != -1) {
    stage.AddCamera(this->ParseCamera(mModel.cameras[node.camera]));
  }

  mat4 mat = identity<mat4>();
  if (node.matrix.size() == 16) {
    for (int i = 0; i < 16; i++) {
      mat[i % 4][i / 4] = node.matrix[i];
    }
  } else {
    vec3 scaling = {1.0f, 1.0f, 1.0f};
    quat rotation = {1.0f, 0.0f, 0.0f, 0.0f};
    vec3 translation = {0.0f, 0.0f, 0.0f};

    if (node.scale.size() == 3) {
      scaling = {node.scale[0], node.scale[1], node.scale[2]};
    }

    if (node.rotation.size() == 4) {
      rotation = {(float)node.rotation[3], (float)node.rotation[0],
                  (float)node.rotation[1], (float)node.rotation[2]};
    }

    if (node.translation.size() == 3) {
      translation = {node.translation[0], node.translation[1],
                     node.translation[2]};
    }

    mat =
        translate(mat, translation) * mat4_cast(rotation) * scale(mat, scaling);
  }
  stage.SetTransform(mat);

  if (node.mesh != -1) {
    Mesh mesh = this->ParseMesh(mModel.meshes[node.mesh]);
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

      this->ParseNode(child, mModel.nodes[index]);
      stage.AddChild(child);
    }
  }
}

void GLTFImporter::ParseModel() {
  if (!mImported) {
    throw Exception::GLTFException("Model not imported");
  }

  for (auto &accessor : mModel.accessors) {
    mAccessors.push_back(this->ParseAccessor(accessor));
  }

  for (auto &skin : mModel.skins) {
    mSkeletonRoots.push_back(skin.skeleton);
  }

  for (auto &scene : mModel.scenes) {
    Stage stage;
    for (auto &index : scene.nodes) {
      if (std::find(mSkeletonRoots.begin(), mSkeletonRoots.end(), index) !=
          mSkeletonRoots.end()) { // Skip skeleton roots
        continue;
      }

      this->ParseNode(stage, mModel.nodes[index]);
    }
  }
}

void GLTFImporter::Import(Str const &path) {
  mLoader.LoadASCIIFromFile(&mModel, &mError, nullptr, path.c_str());
  mImported = true;
}

} // namespace TerreateIO::GLTF
