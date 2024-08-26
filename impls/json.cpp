#include "../includes/json.hpp"

namespace TerreateIO::Parser::Json {
using namespace TerreateIO::Defines;

Str JsonTypeToString(JsonType const &type) {
  switch (type) {
  case JsonType::NULLTYPE:
    return "null";
  case JsonType::BOOLTYPE:
    return "boolean";
  case JsonType::NUMBERTYPE:
    return "number";
  case JsonType::STRINGTYPE:
    return "string";
  case JsonType::ARRAYTYPE:
    return "array";
  case JsonType::OBJECTTYPE:
    return "object";
  }
  return "";
}

void Json::Copy(Json const &json) {
  this->Clear();
  mType = json.mType;
  switch (mType) {
  case JsonType::STRINGTYPE:
    mValue.string = new Str(*json.mValue.string);
    break;
  case JsonType::ARRAYTYPE:
    mValue.array = new Array(*json.mValue.array);
    break;
  case JsonType::OBJECTTYPE:
    mValue.object = new Object(*json.mValue.object);
    break;
  default:
    mValue = json.mValue;
    break;
  }
}

void Json::Clear() {
  switch (mType) {
  case JsonType::STRINGTYPE:
    delete mValue.string;
    break;
  case JsonType::ARRAYTYPE:
    delete mValue.array;
    break;
  case JsonType::OBJECTTYPE:
    delete mValue.object;
    break;
  default:
    break;
  }
}

Json::Json(Json const &json) {
  switch (json.mType) {
  case JsonType::STRINGTYPE:
    mValue.string = new Str(*json.mValue.string);
    break;
  case JsonType::ARRAYTYPE:
    mValue.array = new Array(*json.mValue.array);
    break;
  case JsonType::OBJECTTYPE:
    mValue.object = new Object(*json.mValue.object);
    break;
  default:
    mValue = json.mValue;
    break;
  }
  mType = json.mType;
}

Size Json::GetSize() const {
  switch (mType) {
  case JsonType::ARRAYTYPE:
    return mValue.array->size();
  case JsonType::OBJECTTYPE:
    return mValue.object->size();
  default:
    throw Exception::JsonException("Json is not an array or object");
  }
}

Bool const &Json::GetBool() const {
  if (mType != JsonType::BOOLTYPE) {
    throw Exception::JsonException("Json is not a boolean");
  }
  return mValue.boolean;
}

Double const &Json::GetNumber() const {
  if (mType != JsonType::NUMBERTYPE) {
    throw Exception::JsonException("Json is not a number");
  }
  return mValue.number;
}

Str const &Json::GetString() const {
  if (mType != JsonType::STRINGTYPE) {
    throw Exception::JsonException("Json is not a string");
  }
  return *mValue.string;
}

Array const &Json::GetArray() const {
  if (mType != JsonType::ARRAYTYPE) {
    throw Exception::JsonException("Json is not an array");
  }
  return *mValue.array;
}

Object const &Json::GetObject() const {
  if (mType != JsonType::OBJECTTYPE) {
    throw Exception::JsonException("Json is not an object");
  }
  return *mValue.object;
}

Bool Json::Has(Str const &key) const {
  if (mType != JsonType::OBJECTTYPE) {
    throw Exception::JsonException("Json is not an object");
  }
  return mValue.object->find(key) != mValue.object->end();
}

Json &Json::operator[](Size const &index) {
  if (mType != JsonType::ARRAYTYPE) {
    throw Exception::JsonException("Json is not an array");
  }
  return (*mValue.array)[index];
}

Json &Json::operator[](Str const &key) {
  if (mType != JsonType::OBJECTTYPE) {
    throw Exception::JsonException("Json is not an object");
  }
  return (*mValue.object)[key];
}

Json const &Json::operator[](Size const &index) const {
  if (mType != JsonType::ARRAYTYPE) {
    throw Exception::JsonException("Json is not an array");
  }
  return (*mValue.array)[index];
}

Json const &Json::operator[](Str const &key) const {
  if (mType != JsonType::OBJECTTYPE) {
    throw Exception::JsonException("Json is not an object");
  }
  return (*mValue.object)[key];
}

Json &Json::operator=(Bool const &boolean) {
  this->Clear();
  mValue.boolean = boolean;
  mType = JsonType::BOOLTYPE;
  return *this;
}

Json &Json::operator=(Double const &number) {
  this->Clear();
  mValue.number = number;
  mType = JsonType::NUMBERTYPE;
  return *this;
}

Json &Json::operator=(Str const &string) {
  this->Clear();
  mValue.string = new Str(string);
  mType = JsonType::STRINGTYPE;
  return *this;
}

Json &Json::operator=(Array const &array) {
  this->Clear();
  mValue.array = new Array(array);
  mType = JsonType::ARRAYTYPE;
  return *this;
}

Json &Json::operator=(Object const &object) {
  this->Clear();
  mValue.object = new Object(object);
  mType = JsonType::OBJECTTYPE;
  return *this;
}

Json &Json::operator=(Json const &json) {
  this->Copy(json);
  return *this;
}

Bool JsonParser::ParseNull(Buffer::ReadBuffer &buffer, Json &json) {
  if (buffer.Fetch(4) != "null") {
    return false;
  }

  buffer.Skip(4);
  json = Json();
  return true;
}

Bool JsonParser::ParseBool(Buffer::ReadBuffer &buffer, Json &json) {
  if (buffer.Fetch(4) == "true") {
    buffer.Skip(4);
    json = Json(true);
    return true;
  }

  if (buffer.Fetch(5) == "false") {
    buffer.Skip(5);
    json = Json(false);
    return true;
  }

  return false;
}

Bool JsonParser::ParseNumber(Buffer::ReadBuffer &buffer, Json &json) {
  Str number = "";
  Bool isFloat = false;
  Byte c = buffer.Peek();

  while (c == '-' || c == '.' || c == '+' || c == 'e' || c == 'E' ||
         (c >= '0' && c <= '9')) {
    if (c == '.') {
      isFloat = true;
    }

    number += buffer.Read();
    c = buffer.Peek();
  }

  if (isFloat) {
    json = Json(std::stod(number));
  } else {
    json = Json((Double)std::stoll(number));
  }

  return true;
}

Bool JsonParser::ParseString(Buffer::ReadBuffer &buffer, Json &json) {
  if (buffer.Peek() != '"') {
    return false;
  }

  buffer.Skip(); // Skip the opening quote
  Str string = "";
  Byte c = buffer.Peek();
  while (c != '"') {
    if (c == '\\') {
      buffer.Skip();
      string += ParserBase::Unescape(buffer.Read()[0]);
    } else {
      string += buffer.Read();
    }
    c = buffer.Peek();
  }
  buffer.Skip(); // Skip the closing quote
  json = Json(string);
  return true;
}

Bool JsonParser::ParseArray(Buffer::ReadBuffer &buffer, Json &json) {
  if (buffer.Peek() != '[') {
    return false;
  }

  buffer.Skip(); // Skip the opening bracket
  Array array;
  while (buffer.Peek() != ']') {
    buffer.SkipWhitespace();
    JsonParser parser;
    if (!parser.Parse(buffer)) {
      return false;
    }

    buffer.SkipWhitespace();
    array.push_back(parser.GetRoot());
    if (buffer.Peek() == ',') {
      buffer.Skip();
    }
  }
  buffer.Skip(); // Skip the closing bracket
  json = Json(array);
  return true;
}

Bool JsonParser::ParseObject(Buffer::ReadBuffer &buffer, Json &json) {
  if (buffer.Peek() != '{') {
    return false;
  }

  buffer.Skip(); // Skip the opening brace
  Object object;
  while (buffer.Peek() != '}') {
    buffer.SkipWhitespace();
    Json key;
    if (!this->ParseString(buffer, key)) {
      return false;
    }

    buffer.SkipWhitespace();
    if (buffer.Read() != ":") {
      return false;
    }

    buffer.SkipWhitespace();
    JsonParser parser;
    if (!parser.Parse(buffer)) {
      return false;
    }

    Str keyStr = key.GetString();
    object.insert({keyStr, parser.GetRoot()});
    if (buffer.Peek() == ',') {
      buffer.Skip();
    }
    buffer.SkipWhitespace();
  }
  buffer.Skip(); // Skip the closing brace
  json = Json(object);
  return true;
}

Bool JsonParser::Parse(Buffer::ReadBuffer &buffer) {
  buffer.SkipWhitespace();
  if (buffer.GetSize() == 0) {
    return false;
  }

  switch (buffer.Peek()) {
  case 'n':
    return this->ParseNull(buffer, mRoot);
  case 't':
  case 'f':
    return this->ParseBool(buffer, mRoot);
  case '"':
    return this->ParseString(buffer, mRoot);
  case '[':
    return this->ParseArray(buffer, mRoot);
  case '{':
    return this->ParseObject(buffer, mRoot);
  default:
    return this->ParseNumber(buffer, mRoot);
  }
  return false;
}

Bool JsonParser::Parse() {
  Buffer::ReadBuffer buffer = ParserBase::LoadFile(mFilePath);
  return this->Parse(buffer);
}

} // namespace TerreateIO::Parser::Json

std::ostream &operator<<(std::ostream &os,
                         TerreateIO::Parser::Json::Json const &json) {
  switch (json.GetType()) {
  case TerreateIO::Parser::Json::JsonType::NULLTYPE:
    os << "null";
    break;
  case TerreateIO::Parser::Json::JsonType::BOOLTYPE:
    os << (json.GetBool() ? "true" : "false");
    break;
  case TerreateIO::Parser::Json::JsonType::NUMBERTYPE:
    os << json.GetNumber();
    break;
  case TerreateIO::Parser::Json::JsonType::STRINGTYPE:
    os << "\"" << json.GetString() << "\"";
    break;
  case TerreateIO::Parser::Json::JsonType::ARRAYTYPE:
    os << "[";
    for (TerreateIO::Parser::Json::Size i = 0; i < json.GetSize(); i++) {
      os << json[i];
      if (i < json.GetSize() - 1) {
        os << ", ";
      }
    }
    os << "]";
    break;
  case TerreateIO::Parser::Json::JsonType::OBJECTTYPE:
    os << "{";
    for (TerreateIO::Parser::Json::Size i = 0; i < json.GetSize(); i++) {
      os << "\"" << json.GetObject().begin()->first
         << "\": " << json.GetObject().begin()->second;
      if (i < json.GetSize() - 1) {
        os << ", ";
      }
    }
    os << "}";
    break;
  }
  return os;
}
