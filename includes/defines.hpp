#ifndef __TERREATEIO_DEFINES_HPP__
#define __TERREATEIO_DEFINES_HPP__

#include <TerreateCore/TerreateCore.hpp>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace TerreateIO::Defines {
using namespace TerreateCore::Defines;
using namespace TerreateCore::Utils;

typedef TerreateCore::Core::UUID UUID;
typedef TerreateCore::Core::TerreateObjectBase TerreateObjectBase;
template <enumtype T> using BitFlag = TerreateCore::Core::BitFlag<T>;

using glm::slerp;

inline void FlipImageLoad(Bool const &flip) {
  stbi_set_flip_vertically_on_load(flip);
}

// Used to specify the interpolation type of a keyframe
enum class InterpolationType {
  LINEAR,
  STEP,
  // CUBIC_SPLINE // TODO: Implement cubic spline interpolation
};

enum class MaterialConstant {
  ALPHA,
  EMITTANCE,
  DISCARD,
  NORMAL_SCALE,
  OCCLUSION_STRENGTH,
  METALLIC,
  ROUGHNESS,
  REFRACTION
};

enum class MaterialColor { AMBIENT, DIFFUSE, SPECULAR, EMISSION, BASE };

enum class MaterialTexture {
  AMBIENT,
  DIFFUSE,
  SPECULAR,
  EMISSION,
  NORMAL,
  OCCLUSION,
  BASE_COLOR,
  METALLIC,
  ROUGHNESS,
  METALLIC_ROUGHNESS
};

// Used to specify the alpha mode of a material
enum class AlphaMode { OPAQUE, MASK, BLEND };

// Used to specify the texture filter
enum class TextureFilter {
  NEAREST = 9728,
  LINEAR = 9729,
  NEAREST_MIPMAP_NEAREST = 9984,
  LINEAR_MIPMAP_NEAREST = 9985,
  NEAREST_MIPMAP_LINEAR = 9986,
  LINEAR_MIPMAP_LINEAR = 9987
};

// Used to specify the texture wrapping
enum class TextureWrapping {
  CLAMP_TO_EDGE = 33071,
  MIRRORED_REPEAT = 33648,
  REPEAT = 10497
};
} // namespace TerreateIO::Defines

#endif // __TERREATEIO_DEFINES_HPP__
