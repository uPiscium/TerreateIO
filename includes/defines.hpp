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

typedef TerreateCore::Core::UUID UUID;
typedef TerreateCore::Core::TerreateObjectBase TerreateObjectBase;

inline void FlipImageLoad(Bool const &flip) {
  stbi_set_flip_vertically_on_load(flip);
}
} // namespace TerreateIO::Defines

#endif // __TERREATEIO_DEFINES_HPP__
