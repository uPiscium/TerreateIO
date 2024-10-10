#include "../../includes/container/material.hpp"
#include "../../includes/exceptions.hpp"

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
  TerreateObjectBase::operator=(texture);
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
  TerreateObjectBase::operator=(texture);
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

Material::Material(Material const &material) {
  mMaterialName = material.mMaterialName;
  mDoubleSide = material.mDoubleSide;
  mAlphaMode = material.mAlphaMode;

  mMaterialConstants = material.mMaterialConstants;
  mMaterialColors = material.mMaterialColors;
  mMaterialTextures = material.mMaterialTextures;
  mUVBindings = material.mUVBindings;
}

Material::Material(Material &&material) {
  mMaterialName = material.mMaterialName;
  mDoubleSide = material.mDoubleSide;
  mAlphaMode = material.mAlphaMode;

  mMaterialConstants = std::move(material.mMaterialConstants);
  mMaterialColors = std::move(material.mMaterialColors);
  mMaterialTextures = std::move(material.mMaterialTextures);
  mUVBindings = std::move(material.mUVBindings);
}

Vec<Double> Material::GetConstants() const {
  Vec<Double> constants;
  for (auto const &constant : mMaterialConstants) {
    constants.push_back(constant.second);
  }
  return constants;
}

Vec<Color> Material::GetColors() const {
  Vec<Color> colors;
  for (auto const &color : mMaterialColors) {
    colors.push_back(color.second);
  }
  return colors;
}

Vec<Texture> Material::GetTextures() const {
  Vec<Texture> textures;
  for (auto const &texture : mMaterialTextures) {
    textures.push_back(texture.second);
  }
  return textures;
}

void Material::SetConstant(MaterialConstant const &constant,
                           Double const &value) {
  if (this->HasConstant(constant)) {
    mMaterialConstants[constant] = value;
  } else {
    mMaterialConstants.insert({constant, value});
  }
}

void Material::SetColor(MaterialColor const &color, Color const &value) {
  if (this->HasColor(color)) {
    mMaterialColors[color] = value;
  } else {
    mMaterialColors.insert({color, value});
  }
}

void Material::SetTexture(MaterialTexture const &texture,
                          Texture const &value) {
  if (mMaterialTextures.contains(texture)) {
    mMaterialTextures[texture] = value;
  } else {
    mMaterialTextures.insert({texture, value});
  }
}

void Material::AddUVBinding(MaterialTexture const &type, Str const &binding) {
  if (mUVBindings.find(type) == mUVBindings.end()) {
    mUVBindings.insert({type, binding});
  } else {
    mUVBindings[type] = binding;
  }
}

Double &Material::operator[](MaterialConstant const &constant) {
  if (mMaterialConstants.contains(constant)) {
    return mMaterialConstants[constant];
  } else {
    throw Exception::ContainerException(
        "Material does not contain the specified constant");
  }
}

Color &Material::operator[](MaterialColor const &color) {
  if (mMaterialColors.contains(color)) {
    return mMaterialColors[color];
  } else {
    throw Exception::ContainerException(
        "Material does not contain the specified color");
  }
}

Texture &Material::operator[](MaterialTexture const &texture) {
  if (mMaterialTextures.contains(texture)) {
    return mMaterialTextures[texture];
  } else {
    throw Exception::ContainerException(
        "Material does not contain the specified texture");
  }
}

Double const &Material::operator[](MaterialConstant const &constant) const {
  if (mMaterialConstants.contains(constant)) {
    return mMaterialConstants.at(constant);
  } else {
    throw Exception::ContainerException(
        "Material does not contain the specified constant");
  }
}

Color const &Material::operator[](MaterialColor const &color) const {
  if (mMaterialColors.contains(color)) {
    return mMaterialColors.at(color);
  } else {
    throw Exception::ContainerException(
        "Material does not contain the specified color");
  }
}

Texture const &Material::operator[](MaterialTexture const &texture) const {
  if (mMaterialTextures.contains(texture)) {
    return mMaterialTextures.at(texture);
  } else {
    throw Exception::ContainerException(
        "Material does not contain the specified texture");
  }
}

Material &Material::operator=(Material const &material) {
  TerreateObjectBase::operator=(material);
  mMaterialName = material.mMaterialName;
  mDoubleSide = material.mDoubleSide;
  mAlphaMode = material.mAlphaMode;

  mMaterialConstants = material.mMaterialConstants;
  mMaterialColors = material.mMaterialColors;
  mMaterialTextures = material.mMaterialTextures;
  mUVBindings = material.mUVBindings;

  return *this;
}

Material &Material::operator=(Material &&material) {
  TerreateObjectBase::operator=(material);
  mMaterialName = material.mMaterialName;
  mDoubleSide = material.mDoubleSide;
  mAlphaMode = material.mAlphaMode;

  mMaterialConstants = std::move(material.mMaterialConstants);
  mMaterialColors = std::move(material.mMaterialColors);
  mMaterialTextures = std::move(material.mMaterialTextures);
  mUVBindings = material.mUVBindings;

  return *this;
}
} // namespace TerreateIO::Container
