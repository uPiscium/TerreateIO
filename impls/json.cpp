#include "../includes/json.hpp"
#include "../includes/exceptions.hpp"

namespace TerreateIO::Parser::Json {
using namespace TerreateIO::Defines;

JsonToken::JsonToken(JsonValue const &value, JsonType const &type) {
  switch (type) {
  case JsonType::NULLTYPE:
    mType = JsonType::NULLTYPE;
    mValue.null = (Ubyte)NULL;
    break;
  case JsonType::BOOLTYPE:
    mType = JsonType::BOOLTYPE;
    mValue.boolean = value.boolean;
    break;
  case JsonType::NUMBERTYPE:
    mType = JsonType::NUMBERTYPE;
    mValue.number = value.number;
    break;
  case JsonType::STRTYPE:
    mType = JsonType::STRTYPE;
    mValue.string = new Str(*value.string);
    break;
  case JsonType::ARRAYTYPE:
    mType = JsonType::ARRAYTYPE;
    mValue.array = new JsonArray(*value.array);
    break;
  case JsonType::OBJECTTYPE:
    mType = JsonType::OBJECTTYPE;
    mValue.object = new JsonObject(*value.object);
    break;
  default:
    mType = JsonType::NULLTYPE;
    mValue.null = (Ubyte)NULL;
    break;
  }
}

JsonToken::JsonToken(JsonToken const &token) {
  switch (token.mType) {
  case JsonType::NULLTYPE:
    mType = JsonType::NULLTYPE;
    mValue.null = (Ubyte)NULL;
    break;
  case JsonType::BOOLTYPE:
    mType = JsonType::BOOLTYPE;
    mValue.boolean = token.mValue.boolean;
    break;
  case JsonType::NUMBERTYPE:
    mType = JsonType::NUMBERTYPE;
    mValue.number = token.mValue.number;
    break;
  case JsonType::STRTYPE:
    mType = JsonType::STRTYPE;
    mValue.string = new Str(*token.mValue.string);
    break;
  case JsonType::ARRAYTYPE:
    mType = JsonType::ARRAYTYPE;
    mValue.array = new JsonArray(*token.mValue.array);
    break;
  case JsonType::OBJECTTYPE:
    mType = JsonType::OBJECTTYPE;
    mValue.object = new JsonObject(*token.mValue.object);
    break;
  default:
    mType = JsonType::NULLTYPE;
    mValue.null = (Ubyte)NULL;
    break;
  }
}

JsonToken::JsonToken(JsonToken &&token) {
  switch (token.mType) {
  case JsonType::NULLTYPE:
    mType = JsonType::NULLTYPE;
    mValue.null = (Ubyte)NULL;
    break;
  case JsonType::BOOLTYPE:
    mType = JsonType::BOOLTYPE;
    mValue.boolean = token.mValue.boolean;
    break;
  case JsonType::NUMBERTYPE:
    mType = JsonType::NUMBERTYPE;
    mValue.number = token.mValue.number;
    break;
  case JsonType::STRTYPE:
    mType = JsonType::STRTYPE;
    mValue.string = token.mValue.string;
    token.mValue.string = nullptr;
    break;
  case JsonType::ARRAYTYPE:
    mType = JsonType::ARRAYTYPE;
    mValue.array = token.mValue.array;
    token.mValue.array = nullptr;
    break;
  case JsonType::OBJECTTYPE:
    mType = JsonType::OBJECTTYPE;
    mValue.object = token.mValue.object;
    token.mValue.object = nullptr;
    break;
  default:
    mType = JsonType::NULLTYPE;
    mValue.null = (Ubyte)NULL;
    break;
  }
}

JsonValue &JsonToken::GetValue(Str const &key) {
  if (mType != JsonType::OBJECTTYPE) {
    throw Exception::JsonError("Token is not an object");
  }
  return mValue.object->at(key);
}

JsonValue &JsonToken::GetValue(Uint const &index) {
  if (mType != JsonType::ARRAYTYPE) {
    throw Exception::JsonError("Token is not an array");
  }
  return mValue.array->at(index);
}

Bool const &JsonToken::AcquireBool() const {
  if (mType != JsonType::BOOLTYPE) {
    throw Exception::JsonError("Token is not a boolean");
  }
  return mValue.boolean;
}

Double const &JsonToken::AcquireNumber() const {
  if (mType != JsonType::NUMBERTYPE) {
    throw Exception::JsonError("Token is not a double");
  }
  return mValue.number;
}

Str const &JsonToken::AcquireString() const {
  if (mType != JsonType::STRTYPE) {
    throw Exception::JsonError("Token is not a string");
  }
  return *mValue.string;
}

JsonArray const &JsonToken::AcquireArray() const {
  if (mType != JsonType::ARRAYTYPE) {
    throw Exception::JsonError("Token is not an array");
  }
  return *mValue.array;
}

JsonArray &JsonToken::AcquireArray() {
  if (mType != JsonType::ARRAYTYPE) {
    throw Exception::JsonError("Token is not an array");
  }
  return *mValue.array;
}

JsonObject const &JsonToken::AcquireObject() const {
  if (mType != JsonType::OBJECTTYPE) {
    throw Exception::JsonError("Token is not an object");
  }
  return *mValue.object;
}

JsonObject &JsonToken::AcquireObject() {
  if (mType != JsonType::OBJECTTYPE) {
    throw Exception::JsonError("Token is not an object");
  }
  return *mValue.object;
}

void JsonToken::SetValue() {
  this->Clear();
  mType = JsonType::NULLTYPE;
  mValue.null = (Ubyte)NULL;
}

void JsonToken::SetValue(Bool const &value) {
  this->Clear();
  mType = JsonType::BOOLTYPE;
  mValue.boolean = value;
}

void JsonToken::SetValue(Double const &value) {
  this->Clear();
  mType = JsonType::NUMBERTYPE;
  mValue.number = value;
}

void JsonToken::SetValue(Str const &value) {
  this->Clear();
  mType = JsonType::STRTYPE;
  mValue.string = new Str(value);
}

void JsonToken::SetValue(JsonArray const &value) {
  this->Clear();
  mType = JsonType::ARRAYTYPE;
  mValue.array = new JsonArray(value);
}

void JsonToken::SetValue(JsonObject const &value) {
  this->Clear();
  mType = JsonType::OBJECTTYPE;
  mValue.object = new JsonObject(value);
}

Bool JsonToken::Has(Str const &key) const {
  if (mType != JsonType::OBJECTTYPE) {
    return false;
  }
  return mValue.object->find(key) != mValue.object->end();
}

Size JsonToken::Size() const {
  if (mType == JsonType::ARRAYTYPE) {
    return mValue.array->size();
  }
  if (mType == JsonType::OBJECTTYPE) {
    return mValue.object->size();
  }
  return 0;
}

void JsonToken::Clear() {
  if (mType == JsonType::STRTYPE) {
    delete mValue.string;
  }
  if (mType == JsonType::ARRAYTYPE) {
    delete mValue.array;
  }
  if (mType == JsonType::OBJECTTYPE) {
    delete mValue.object;
  }

  mType = JsonType::NULLTYPE;
  mValue.null = (Ubyte)NULL;
}

JsonToken &JsonToken::operator=(JsonToken const &token) {
  if (this == &token) {
    return *this;
  }

  this->SetValue(token.mValue);
  return *this;
}

JsonToken &JsonToken::operator=(JsonToken &&token) {
  if (this == &token) {
    return *this;
  }

  this->SetValue(token.mValue);
  return *this;
}

JsonToken &JsonToken::operator=(Bool const &value) {
  this->SetValue(value);
  return *this;
}

JsonToken &JsonToken::operator=(Double const &value) {
  this->SetValue(value);
  return *this;
}

JsonToken &JsonToken::operator=(Str const &value) {
  this->SetValue(value);
  return *this;
}

JsonToken &JsonToken::operator=(JsonArray const &value) {
  this->SetValue(value);
  return *this;
}

JsonToken &JsonToken::operator=(JsonObject const &value) {
  this->SetValue(value);
  return *this;
}

JsonType JsonParser::Next() { ; }

Bool JsonParser::ParseNull(JsonToken &token) {
  if (Reader::Fetch(4, mBuffer) != "null") {
    return false;
  }
  Reader::Skip(4, mBuffer); // Skip "null"
  token.SetValue();
  return true;
}

Bool JsonParser::ParseBool(JsonToken &token) {
  if (Reader::Fetch(4, mBuffer) == "true") {
    Reader::Skip(4, mBuffer); // Skip "true"
    token.SetValue(true);
    return true;
  }
  if (Reader::Fetch(5, mBuffer) == "false") {
    Reader::Skip(5, mBuffer); // Skip "false"
    token.SetValue(false);
    return true;
  }
  return false;
}

Bool JsonParser::ParseNumber(JsonToken &token) {
  Stream stream;
  Bool loop = true;
  while (loop) {
    Byte const &chr = Reader::Fetch(1, mBuffer)[0];
    if (chr == '.' || chr == 'e' || chr == 'E') {
      stream << Reader::Read(1, mBuffer);
    } else if (chr == '-' || chr == '+' || (chr >= '0' && chr <= '9')) {
      stream << Reader::Read(1, mBuffer);
    } else {
      loop = false;
    }
  }
  token.SetValue(std::stod(stream.str()));
  return true;
}

Bool JsonParser::ParseString(JsonToken &token);

Bool JsonParser::ParseArray(JsonToken &token);

Bool JsonParser::ParseObject(JsonToken &token);

} // namespace TerreateIO::Parser::Json
