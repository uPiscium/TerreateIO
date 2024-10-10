#ifndef __TERREATEIO_MODEL_MATERIAL_HPP__
#define __TERREATEIO_MODEL_MATERIAL_HPP__

#include "../defines.hpp"

namespace TerreateIO::Container {
using namespace TerreateIO::Defines;
using namespace TerreateCore::Math;

struct Color {
  Double r = 0.0;
  Double g = 0.0;
  Double b = 0.0;
  Double a = 0.0;

  Color() = default;
  Color(Double const &red, Double const &green, Double const &blue,
        Double const &alpha = 1.0)
      : r(red), g(green), b(blue), a(alpha) {}
  Color(Color const &color) : r(color.r), g(color.g), b(color.b), a(color.a) {}

  Color &operator=(Color const &color);
};

struct Texture : public TerreateObjectBase {
  Ubyte *data = nullptr;
  Uint width = 0u;
  Uint height = 0u;
  Uint channels = 0u;
  TextureFilter minFilter = TextureFilter::NEAREST;
  TextureFilter magFilter = TextureFilter::NEAREST;
  TextureWrapping wrapS = TextureWrapping::REPEAT;
  TextureWrapping wrapT = TextureWrapping::REPEAT;

  Texture() = default;
  Texture(Ubyte *const &textureData, Uint const &textureWidth,
          Uint const &textureHeight, Uint const &textureChannels)
      : data(textureData), width(textureWidth), height(textureHeight),
        channels(textureChannels) {}
  Texture(Texture const &texture);
  Texture(Texture &&texture);
  ~Texture();

  Texture &operator=(Texture const &texture);
  Texture &operator=(Texture &&texture);
};

class Material : public TerreateObjectBase {
private:
  Str mMaterialName = "";
  Bool mDoubleSide = false;
  AlphaMode mAlphaMode = AlphaMode::OPAQUE;

  Map<MaterialConstant, Double> mMaterialConstants;
  Map<MaterialColor, Color> mMaterialColors;
  Map<MaterialTexture, Texture> mMaterialTextures;
  Map<MaterialTexture, Str> mUVBindings;

public:
  Material() = default;
  Material(Str const &name) : mMaterialName(name) {}
  Material(Material const &material);
  Material(Material &&material);
  ~Material() = default;

  Str const &GetMaterialName() const { return mMaterialName; }
  AlphaMode const &GetAlphaMode() const { return mAlphaMode; }
  Double const &GetConstant(MaterialConstant const &constant) const {
    return mMaterialConstants.at(constant);
  }
  Color const &GetColor(MaterialColor const &color) const {
    return mMaterialColors.at(color);
  }
  Texture const &GetTexture(MaterialTexture const &texture) const {
    return mMaterialTextures.at(texture);
  }
  Vec<Double> GetConstants() const;
  Vec<Color> GetColors() const;
  Vec<Texture> GetTextures() const;
  Map<MaterialTexture, Str> const &GetUVBindings() const { return mUVBindings; }
  Str const &GetUVBinding(MaterialTexture const &type) const {
    return mUVBindings.at(type);
  }

  Bool const &IsDoubleSide() const { return mDoubleSide; }

  Bool HasConstant(MaterialConstant const &constant) const {
    return mMaterialConstants.contains(constant);
  }
  Bool HasColor(MaterialColor const &color) const {
    return mMaterialColors.contains(color);
  }
  Bool HasTexture(MaterialTexture const &texture) const {
    return mMaterialTextures.contains(texture);
  }

  void SetDoubleSide(Bool const &doubleSide) { mDoubleSide = doubleSide; }
  void SetMaterialName(Str const &name) { mMaterialName = name; }
  void SetAlphaMode(AlphaMode const &mode) { mAlphaMode = mode; }
  void SetConstant(MaterialConstant const &constant, Double const &value);
  void SetColor(MaterialColor const &color, Color const &value);
  void SetTexture(MaterialTexture const &texture, Texture const &value);

  void AddUVBinding(MaterialTexture const &type, Str const &binding);

  Double &operator[](MaterialConstant const &constant);
  Color &operator[](MaterialColor const &color);
  Texture &operator[](MaterialTexture const &texture);
  Double const &operator[](MaterialConstant const &constant) const;
  Color const &operator[](MaterialColor const &color) const;
  Texture const &operator[](MaterialTexture const &texture) const;

  Material &operator=(Material const &material);
  Material &operator=(Material &&material);
};
} // namespace TerreateIO::Container

#endif // __TERREATEIO_MODEL_MATERIAL_HPP__
