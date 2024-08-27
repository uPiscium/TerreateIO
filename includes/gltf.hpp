#ifndef __TERREATEIO_GLTF_HPP__
#define __TERREATEIO_GLTF_HPP__

#include "buffer.hpp"
#include "composer.hpp"
#include "defines.hpp"
#include "json.hpp"
#include "parser.hpp"

namespace TerreateIO::glTF {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;

typedef Json::JsonParser JsonParser;

class GLTFParser : public ParserBase {
  ;
};

class GLTFComposer : public ComposerBase {
  ;
};
} // namespace TerreateIO::glTF

#endif // __TERREATEIO_GLTF_HPP__
