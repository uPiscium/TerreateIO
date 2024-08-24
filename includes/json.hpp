#ifndef __TERREATEIO_JSON_HPP__
#define __TERREATEIO_JSON_HPP__

#include "defines.hpp"

namespace TerreateIO::Parser::Json {
using namespace TerreateIO::Defines;

union JsonValue;

typedef Vec<JsonValue> Array;
typedef Map<Str, JsonValue> Object;

enum class JsonType {
  NULLTYPE,
  BOOLTYPE,
  NUMBERTYPE,
  STRINGTYPE,
  ARRAYTYPE,
  OBJECTTYPE
};

union JsonValue {
  Bool boolean;
  Double number;
  Str *string;
  Array *array;
  Object *object;
};

class JsonParser {
  ;
};
} // namespace TerreateIO::Parser::Json

#endif // __TERREATEIO_JSON_HPP__
