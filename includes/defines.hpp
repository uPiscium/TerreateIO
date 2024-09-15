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
} // namespace TerreateIO::Defines

#endif // __TERREATEIO_DEFINES_HPP__
