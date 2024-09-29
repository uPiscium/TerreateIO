#include "../../includes/container/material.hpp"

namespace TerreateIO::Container {
using namespace TerreateIO::Defines;

Color &Color::operator=(Color const &color) {
  r = color.r;
  g = color.g;
  b = color.b;
  a = color.a;

  return *this;
}

Texture::Texture(Texture const &texture) {
  data = new Ubyte[texture.width * texture.height * texture.channels];
  std::memcpy(data, texture.data,
              texture.width * texture.height * texture.channels);
  width = texture.width;
  height = texture.height;
  channels = texture.channels;
}

Texture::Texture(Texture &&texture) {
  data = texture.data;
  width = texture.width;
  height = texture.height;
  channels = texture.channels;

  texture.data = nullptr;
  texture.width = 0u;
  texture.height = 0u;
  texture.channels = 0u;
}

Texture::~Texture() {
  if (data != nullptr) {
    delete[] data;
    data = nullptr;
  }
}

Texture &Texture::operator=(Texture const &texture) {
  if (data != nullptr) {
    delete[] data;
    data = nullptr;
  }

  data = new Ubyte[texture.width * texture.height * texture.channels];
  std::memcpy(data, texture.data,
              texture.width * texture.height * texture.channels);
  width = texture.width;
  height = texture.height;
  channels = texture.channels;

  return *this;
}

Texture &Texture::operator=(Texture &&texture) {
  if (data != nullptr) {
    delete[] data;
    data = nullptr;
  }

  data = texture.data;
  width = texture.width;
  height = texture.height;
  channels = texture.channels;

  texture.data = nullptr;
  texture.width = 0u;
  texture.height = 0u;
  texture.channels = 0u;

  return *this;
}

PBR::PBR(PBR const &pbr) {
  metallic = pbr.metallic;
  roughness = pbr.roughness;
  refraction = pbr.refraction;

  baseColorTexture = pbr.baseColorTexture;
  metallicTexture = pbr.metallicTexture;
  roughnessTexture = pbr.roughnessTexture;
  metallicRoughnessTexture = pbr.metallicRoughnessTexture;
}

PBR::PBR(PBR &&pbr) {
  metallic = pbr.metallic;
  roughness = pbr.roughness;
  refraction = pbr.refraction;

  baseColorTexture = std::move(pbr.baseColorTexture);
  metallicTexture = std::move(pbr.metallicTexture);
  roughnessTexture = std::move(pbr.roughnessTexture);
  metallicRoughnessTexture = std::move(pbr.metallicRoughnessTexture);
}

PBR &PBR::operator=(PBR const &pbr) {
  metallic = pbr.metallic;
  roughness = pbr.roughness;
  refraction = pbr.refraction;

  baseColorTexture = pbr.baseColorTexture;
  metallicTexture = pbr.metallicTexture;
  roughnessTexture = pbr.roughnessTexture;
  metallicRoughnessTexture = pbr.metallicRoughnessTexture;

  return *this;
}

PBR &PBR::operator=(PBR &&pbr) {
  metallic = pbr.metallic;
  roughness = pbr.roughness;
  refraction = pbr.refraction;

  baseColorTexture = std::move(pbr.baseColorTexture);
  metallicTexture = std::move(pbr.metallicTexture);
  roughnessTexture = std::move(pbr.roughnessTexture);
  metallicRoughnessTexture = std::move(pbr.metallicRoughnessTexture);

  return *this;
}

Material::Material(Material const &material) {
  mMaterialName = material.mMaterialName;
  mDoubleSide = material.mDoubleSide;
  mPBR = material.mPBR;

  mAlpha = material.mAlpha;
  mEmittance = material.mEmittance;
  mDiscard = material.mDiscard;

  mAmbientColor = material.mAmbientColor;
  mDiffuseColor = material.mDiffuseColor;
  mSpecularColor = material.mSpecularColor;
  mEmissiveColor = material.mEmissiveColor;

  mAmbientTexture = material.mAmbientTexture;
  mDiffuseTexture = material.mDiffuseTexture;
  mSpecularTexture = material.mSpecularTexture;
  mEmissiveTexture = material.mEmissiveTexture;
  mNormalTexture = material.mNormalTexture;
  mOcclusionTexture = material.mOcclusionTexture;

  mPBRData = material.mPBRData;
}

Material::Material(Material &&material) {
  mMaterialName = material.mMaterialName;
  mDoubleSide = material.mDoubleSide;
  mPBR = material.mPBR;

  mAlpha = material.mAlpha;
  mEmittance = material.mEmittance;
  mDiscard = material.mDiscard;

  mAmbientColor = material.mAmbientColor;
  mDiffuseColor = material.mDiffuseColor;
  mSpecularColor = material.mSpecularColor;
  mEmissiveColor = material.mEmissiveColor;

  mAmbientTexture = std::move(material.mAmbientTexture);
  mDiffuseTexture = std::move(material.mDiffuseTexture);
  mSpecularTexture = std::move(material.mSpecularTexture);
  mEmissiveTexture = std::move(material.mEmissiveTexture);
  mNormalTexture = std::move(material.mNormalTexture);
  mOcclusionTexture = std::move(material.mOcclusionTexture);

  mPBRData = std::move(material.mPBRData);
}

Material &Material::operator=(Material const &material) {
  mMaterialName = material.mMaterialName;
  mDoubleSide = material.mDoubleSide;
  mPBR = material.mPBR;

  mAlpha = material.mAlpha;
  mEmittance = material.mEmittance;
  mDiscard = material.mDiscard;

  mAmbientColor = material.mAmbientColor;
  mDiffuseColor = material.mDiffuseColor;
  mSpecularColor = material.mSpecularColor;
  mEmissiveColor = material.mEmissiveColor;

  mAmbientTexture = material.mAmbientTexture;
  mDiffuseTexture = material.mDiffuseTexture;
  mSpecularTexture = material.mSpecularTexture;
  mEmissiveTexture = material.mEmissiveTexture;
  mNormalTexture = material.mNormalTexture;
  mOcclusionTexture = material.mOcclusionTexture;

  mPBRData = material.mPBRData;

  return *this;
}

Material &Material::operator=(Material &&material) {
  mMaterialName = material.mMaterialName;
  mDoubleSide = material.mDoubleSide;
  mPBR = material.mPBR;

  mAlpha = material.mAlpha;
  mEmittance = material.mEmittance;
  mDiscard = material.mDiscard;

  mAmbientColor = material.mAmbientColor;
  mDiffuseColor = material.mDiffuseColor;
  mSpecularColor = material.mSpecularColor;
  mEmissiveColor = material.mEmissiveColor;

  mAmbientTexture = std::move(material.mAmbientTexture);
  mDiffuseTexture = std::move(material.mDiffuseTexture);
  mSpecularTexture = std::move(material.mSpecularTexture);
  mEmissiveTexture = std::move(material.mEmissiveTexture);
  mNormalTexture = std::move(material.mNormalTexture);
  mOcclusionTexture = std::move(material.mOcclusionTexture);

  mPBRData = std::move(material.mPBRData);

  return *this;
}
} // namespace TerreateIO::Container
