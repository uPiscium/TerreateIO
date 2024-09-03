#ifndef __TERREATEIO_MODEL_MATERIAL_HPP__
#define __TERREATEIO_MODEL_MATERIAL_HPP__

#include "../defines.hpp"

namespace TerreateIO::Model {
using namespace TerreateIO::Defines;

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

struct Texture {
  Ubyte *data = nullptr;
  Uint width = 0u;
  Uint height = 0u;
  Uint channels = 0u;

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

struct PBR {
  Double metallic = 0.0;
  Double roughness = 0.0;
  Double refraction = 0.0;

  Texture baseColorTexture;
  Texture metallicTexture;
  Texture roughnessTexture;
  Texture metallicRoughnessTexture;

  PBR() = default;
  PBR(Double const &metallicValue, Double const &roughnessValue,
      Double const &refractionValue)
      : metallic(metallicValue), roughness(roughnessValue),
        refraction(refractionValue) {}
  PBR(PBR const &pbr);
  PBR(PBR &&pbr);

  PBR &operator=(PBR const &pbr);
  PBR &operator=(PBR &&pbr);
};

class Material : public TerreateObjectBase {
private:
  Str mMaterialName = "";
  Bool mDoubleSide = false;
  Bool mPBR = false;

  Double mAlpha = 0.0;
  Double mEmittance = 0.0;
  Double mDiscard = 0.0;

  Color mAmbientColor;
  Color mDiffuseColor;
  Color mSpecularColor;
  Color mEmissiveColor;

  Texture mAmbientTexture;
  Texture mDiffuseTexture;
  Texture mSpecularTexture;
  Texture mEmissiveTexture;
  Texture mNormalTexture;
  Texture mOcclusionTexture;

  PBR mPBRData;

public:
  Material() = default;
  Material(Str const &name) : mMaterialName(name) {}
  Material(Material const &material);
  Material(Material &&material);
  ~Material();

  Str const &GetMaterialName() const { return mMaterialName; }
  Double const &GetAlpha() const { return mAlpha; }
  Double const &GetEmittance() const { return mEmittance; }
  Double const &GetDiscard() const { return mDiscard; }
  Color const &GetAmbientColor() const { return mAmbientColor; }
  Color const &GetDiffuseColor() const { return mDiffuseColor; }
  Color const &GetSpecularColor() const { return mSpecularColor; }
  Color const &GetEmissiveColor() const { return mEmissiveColor; }
  Texture const &GetAmbientTexture() const { return mAmbientTexture; }
  Texture const &GetDiffuseTexture() const { return mDiffuseTexture; }
  Texture const &GetSpecularTexture() const { return mSpecularTexture; }
  Texture const &GetEmissiveTexture() const { return mEmissiveTexture; }
  Texture const &GetNormalTexture() const { return mNormalTexture; }
  Texture const &GetOcclusionTexture() const { return mOcclusionTexture; }
  PBR const &GetPBRData() const { return mPBRData; }

  Bool const &IsDoubleSide() const { return mDoubleSide; }
  Bool const &IsPBR() const { return mPBR; }

  void SetMaterialName(Str const &name) { mMaterialName = name; }
  void SetAlpha(Double const &alpha) { mAlpha = alpha; }
  void SetEmittance(Double const &emittance) { mEmittance = emittance; }
  void SetDiscard(Double const &discard) { mDiscard = discard; }
  void SetAmbientColor(Color const &color) { mAmbientColor = color; }
  void SetDiffuseColor(Color const &color) { mDiffuseColor = color; }
  void SetSpecularColor(Color const &color) { mSpecularColor = color; }
  void SetEmissiveColor(Color const &color) { mEmissiveColor = color; }
  void SetAmbientTexture(Texture const &texture) { mAmbientTexture = texture; }
  void SetDiffuseTexture(Texture const &texture) { mDiffuseTexture = texture; }
  void SetSpecularTexture(Texture const &texture) {
    mSpecularTexture = texture;
  }
  void SetEmissiveTexture(Texture const &texture) {
    mEmissiveTexture = texture;
  }
  void SetNormalTexture(Texture const &texture) { mNormalTexture = texture; }
  void SetOcclusionTexture(Texture const &texture) {
    mOcclusionTexture = texture;
  }
  void SetPBRData(PBR const &data) { mPBRData = data; }
  void SetAmbientTexture(Texture &&texture) {
    mAmbientTexture = std::move(texture);
  }
  void SetDiffuseTexture(Texture &&texture) {
    mDiffuseTexture = std::move(texture);
  }
  void SetSpecularTexture(Texture &&texture) {
    mSpecularTexture = std::move(texture);
  }
  void SetEmissiveTexture(Texture &&texture) {
    mEmissiveTexture = std::move(texture);
  }
  void SetNormalTexture(Texture &&texture) {
    mNormalTexture = std::move(texture);
  }
  void SetOcclusionTexture(Texture &&texture) {
    mOcclusionTexture = std::move(texture);
  }
  void SetPBRData(PBR &&data) { mPBRData = std::move(data); }

  Material &operator=(Material const &material);
  Material &operator=(Material &&material);
};
} // namespace TerreateIO::Model

#endif // __TERREATEIO_MODEL_MATERIAL_HPP__
