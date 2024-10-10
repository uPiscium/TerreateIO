#include "../../includes/io/json.hpp"
#include "../../includes/exceptions.hpp"

namespace TerreateIO::JSON {
using namespace TerreateIO::Defines;

namespace Utils {
Bool Extract(JSON const &json, Str const &key, JSON &value) {
  if (!json.IsObject()) {
    throw Exception::GLTFException("JSON is not an object");
  }

  if (!json.Has(key)) {
    return false;
  }

  value = json[key];
  return true;
}

Bool Extract(JSON const &json, Str const &key, Bool &value) {
  JSON val;
  if (!Extract(json, key, val)) {
    return false;
  }

  if (!val.IsBool()) {
    throw Exception::GLTFException("JSON value is not a boolean");
  }

  value = val.GetBool();
  return true;
}

Bool Extract(JSON const &json, Str const &key, Double &value) {
  JSON val;
  if (!Extract(json, key, val)) {
    return false;
  }

  if (!val.IsNumber()) {
    throw Exception::GLTFException("JSON value is not a number");
  }

  value = val.GetNumber();
  return true;
}

Bool Extract(JSON const &json, Str const &key, Str &value) {
  JSON val;
  if (!Extract(json, key, val)) {
    return false;
  }

  if (!val.IsString()) {
    throw Exception::GLTFException("JSON value is not a string");
  }

  value = val.GetString();
  return true;
}

Bool Extract(JSON const &json, Str const &key, Array &value) {
  JSON val;
  if (!Extract(json, key, val)) {
    return false;
  }

  if (!val.IsArray()) {
    throw Exception::GLTFException("JSON value is not an array");
  }

  value = val.GetArray();
  return true;
}

Bool Extract(JSON const &json, Str const &key, Object &value) {
  JSON val;
  if (!Extract(json, key, val)) {
    return false;
  }

  if (!val.IsObject()) {
    throw Exception::GLTFException("JSON value is not an object");
  }

  value = val.GetObject();
  return true;
}

Bool Extract(JSON const &json, Str const &key, Vec<Bool> &value) {
  Array arr;
  if (!Extract(json, key, arr)) {
    return false;
  }

  for (auto &elem : arr) {
    if (!elem.IsBool()) {
      throw Exception::GLTFException("JSON array element is not a boolean");
    }
    value.push_back(elem.GetBool());
  }

  return true;
}

Bool Extract(JSON const &json, Str const &key, Vec<Double> &value) {
  Array arr;
  if (!Extract(json, key, arr)) {
    return false;
  }

  for (auto &elem : arr) {
    if (!elem.IsNumber()) {
      throw Exception::GLTFException("JSON array element is not a number");
    }
    value.push_back(elem.GetNumber());
  }

  return true;
}

Bool Extract(JSON const &json, Str const &key, Vec<Str> &value) {
  Array arr;
  if (!Extract(json, key, arr)) {
    return false;
  }

  for (auto &elem : arr) {
    if (!elem.IsString()) {
      throw Exception::GLTFException("JSON array element is not a string");
    }
    value.push_back(elem.GetString());
  }

  return true;
}

Bool Extract(JSON const &json, Str const &key, Map<Str, Bool> &value) {
  Object obj;
  if (!Extract(json, key, obj)) {
    return false;
  }

  for (auto &pair : obj) {
    if (!pair.second.IsBool()) {
      throw Exception::GLTFException("JSON object value is not a boolean");
    }
    value.insert({pair.first, pair.second.GetBool()});
  }

  return true;
}

Bool Extract(JSON const &json, Str const &key, Map<Str, Double> &value) {
  Object obj;
  if (!Extract(json, key, obj)) {
    return false;
  }

  for (auto &pair : obj) {
    if (!pair.second.IsNumber()) {
      throw Exception::GLTFException("JSON object value is not a number");
    }
    value.insert({pair.first, pair.second.GetNumber()});
  }

  return true;
}

Bool Extract(JSON const &json, Str const &key, Map<Str, Str> &value) {
  Object obj;
  if (!Extract(json, key, obj)) {
    return false;
  }

  for (auto &pair : obj) {
    if (!pair.second.IsString()) {
      throw Exception::GLTFException("JSON object value is not a string");
    }
    value.insert({pair.first, pair.second.GetString()});
  }

  return true;
}

Str JSONTypeToString(JSONType const &type) {
  switch (type) {
  case JSONType::NULLTYPE:
    return "null";
  case JSONType::BOOLTYPE:
    return "boolean";
  case JSONType::NUMBERTYPE:
    return "number";
  case JSONType::STRINGTYPE:
    return "string";
  case JSONType::ARRAYTYPE:
    return "array";
  case JSONType::OBJECTTYPE:
    return "object";
  }
  return "";
}
} // namespace Utils

void JSON::Copy(JSON const &json) {
  this->Clear();
  mType = json.mType;
  switch (mType) {
  case JSONType::STRINGTYPE:
    mValue.string = new Str(*json.mValue.string);
    break;
  case JSONType::ARRAYTYPE:
    mValue.array = new Array(*json.mValue.array);
    break;
  case JSONType::OBJECTTYPE:
    mValue.object = new Object(*json.mValue.object);
    break;
  default:
    mValue = json.mValue;
    break;
  }
}

void JSON::Clear() {
  switch (mType) {
  case JSONType::STRINGTYPE:
    delete mValue.string;
    break;
  case JSONType::ARRAYTYPE:
    delete mValue.array;
    break;
  case JSONType::OBJECTTYPE:
    delete mValue.object;
    break;
  default:
    break;
  }
}

JSON::JSON(JSON const &json) {
  switch (json.mType) {
  case JSONType::STRINGTYPE:
    mValue.string = new Str(*json.mValue.string);
    break;
  case JSONType::ARRAYTYPE:
    mValue.array = new Array(*json.mValue.array);
    break;
  case JSONType::OBJECTTYPE:
    mValue.object = new Object(*json.mValue.object);
    break;
  default:
    mValue = json.mValue;
    break;
  }
  mType = json.mType;
}

Size JSON::GetSize() const {
  switch (mType) {
  case JSONType::ARRAYTYPE:
    return mValue.array->size();
  case JSONType::OBJECTTYPE:
    return mValue.object->size();
  default:
    throw Exception::JSONException("JSON is not an array or object");
  }
}

Vec<Str> JSON::GetKeys() const {
  if (mType != JSONType::OBJECTTYPE) {
    throw Exception::JSONException("JSON is not an object");
  }

  Vec<Str> keys;
  for (auto const &pair : *mValue.object) {
    keys.push_back(pair.first);
  }
  return keys;
}

Array JSON::GetValues() const {
  if (mType != JSONType::OBJECTTYPE) {
    throw Exception::JSONException("JSON is not an object");
  }

  Array values;
  for (auto const &pair : *mValue.object) {
    values.push_back(pair.second);
  }
  return values;
}

Bool const &JSON::GetBool() const {
  if (mType != JSONType::BOOLTYPE) {
    throw Exception::JSONException("JSON is not a boolean");
  }
  return mValue.boolean;
}

Double const &JSON::GetNumber() const {
  if (mType != JSONType::NUMBERTYPE) {
    throw Exception::JSONException("JSON is not a number");
  }
  return mValue.number;
}

Str const &JSON::GetString() const {
  if (mType != JSONType::STRINGTYPE) {
    throw Exception::JSONException("JSON is not a string");
  }
  return *mValue.string;
}

Array const &JSON::GetArray() const {
  if (mType != JSONType::ARRAYTYPE) {
    throw Exception::JSONException("JSON is not an array");
  }
  return *mValue.array;
}

Object const &JSON::GetObject() const {
  if (mType != JSONType::OBJECTTYPE) {
    throw Exception::JSONException("JSON is not an object");
  }
  return *mValue.object;
}

Bool JSON::Has(Str const &key) const {
  if (mType != JSONType::OBJECTTYPE) {
    throw Exception::JSONException("JSON is not an object");
  }
  return mValue.object->find(key) != mValue.object->end();
}

JSON &JSON::operator[](Size const &index) {
  if (mType != JSONType::ARRAYTYPE) {
    throw Exception::JSONException("JSON is not an array");
  }
  return (*mValue.array)[index];
}

JSON &JSON::operator[](Str const &key) {
  if (mType != JSONType::OBJECTTYPE) {
    throw Exception::JSONException("JSON is not an object");
  }
  return (*mValue.object)[key];
}

JSON const &JSON::operator[](Size const &index) const {
  if (mType != JSONType::ARRAYTYPE) {
    throw Exception::JSONException("JSON is not an array");
  }
  return (*mValue.array)[index];
}

JSON const &JSON::operator[](Str const &key) const {
  if (mType != JSONType::OBJECTTYPE) {
    throw Exception::JSONException("JSON is not an object");
  }
  return (*mValue.object)[key];
}

JSON &JSON::operator=(Bool const &boolean) {
  this->Clear();
  mValue.boolean = boolean;
  mType = JSONType::BOOLTYPE;
  return *this;
}

JSON &JSON::operator=(Double const &number) {
  this->Clear();
  mValue.number = number;
  mType = JSONType::NUMBERTYPE;
  return *this;
}

JSON &JSON::operator=(Str const &string) {
  this->Clear();
  mValue.string = new Str(string);
  mType = JSONType::STRINGTYPE;
  return *this;
}

JSON &JSON::operator=(Array const &array) {
  this->Clear();
  mValue.array = new Array(array);
  mType = JSONType::ARRAYTYPE;
  return *this;
}

JSON &JSON::operator=(Object const &object) {
  this->Clear();
  mValue.object = new Object(object);
  mType = JSONType::OBJECTTYPE;
  return *this;
}

JSON &JSON::operator=(JSON const &json) {
  this->Copy(json);
  return *this;
}

Bool JSONParser::ParseNull(ReadBuffer &buffer, JSON &json) {
  if (buffer.Fetch(4) != "null") {
    return false;
  }

  buffer.Skip(4);
  json = JSON();
  return true;
}

Bool JSONParser::ParseBool(ReadBuffer &buffer, JSON &json) {
  if (buffer.Fetch(4) == "true") {
    buffer.Skip(4);
    json = JSON(true);
    return true;
  }

  if (buffer.Fetch(5) == "false") {
    buffer.Skip(5);
    json = JSON(false);
    return true;
  }

  return false;
}

Bool JSONParser::ParseNumber(ReadBuffer &buffer, JSON &json) {
  Str number = "";
  Bool isFloat = false;
  Byte c = buffer.Fetch();

  while (c == '-' || c == '.' || c == '+' || c == 'e' || c == 'E' ||
         (c >= '0' && c <= '9')) {
    if (c == '.') {
      isFloat = true;
    }

    number += buffer.Read();
    c = buffer.Fetch();
  }

  if (isFloat) {
    json = JSON(std::stod(number));
  } else {
    json = JSON((Double)std::stoll(number));
  }

  return true;
}

Bool JSONParser::ParseString(ReadBuffer &buffer, JSON &json) {
  if (buffer.Fetch() != '"') {
    return false;
  }

  buffer.Skip(); // Skip the opening quote
  Str string = "";
  Byte c = buffer.Fetch();
  while (c != '"') {
    if (c == '\\') {
      buffer.Skip();
      string += ParserBase::Unescape(buffer.Read());
    } else {
      string += buffer.Read();
    }
    c = buffer.Fetch();
  }
  buffer.Skip(); // Skip the closing quote
  json = JSON(string);
  return true;
}

Bool JSONParser::ParseArray(ReadBuffer &buffer, JSON &json) {
  if (buffer.Fetch() != '[') {
    return false;
  }

  buffer.Skip(); // Skip the opening bracket
  Array array;
  while (buffer.Fetch() != ']') {
    buffer.SkipWhitespace();
    JSONParser parser;
    if (!parser.Parse(buffer)) {
      return false;
    }

    buffer.SkipWhitespace();
    array.push_back(parser.GetRoot());
    if (buffer.Fetch() == ',') {
      buffer.Skip();
    }
  }
  buffer.Skip(); // Skip the closing bracket
  json = JSON(array);
  return true;
}

Bool JSONParser::ParseObject(ReadBuffer &buffer, JSON &json) {
  if (buffer.Fetch() != '{') {
    return false;
  }

  buffer.Skip(); // Skip the opening brace
  Object object;
  while (buffer.Fetch() != '}') {
    buffer.SkipWhitespace();
    JSON key;
    if (!this->ParseString(buffer, key)) {
      return false;
    }

    buffer.SkipWhitespace();
    if (buffer.Read() != ':') {
      return false;
    }

    buffer.SkipWhitespace();
    JSONParser parser;
    if (!parser.Parse(buffer)) {
      return false;
    }

    Str keyStr = key.GetString();
    object.insert({keyStr, parser.GetRoot()});
    if (buffer.Fetch() == ',') {
      buffer.Skip();
    }
    buffer.SkipWhitespace();
  }
  buffer.Skip(); // Skip the closing brace
  json = JSON(object);
  return true;
}

Bool JSONParser::Parse(ReadBuffer &buffer) {
  buffer.SkipWhitespace();
  if (buffer.GetSize() == 0) {
    return false;
  }

  switch (buffer.Fetch()) {
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

Bool JSONParser::Parse() {
  ReadBuffer buffer = ParserBase::LoadFile(mFilePath);
  return this->Parse(buffer);
}

void JSONComposer::Indent(WriteBuffer &buffer, Size const &indent) {
  buffer.Write('\n');
  for (Size i = 0; i < indent; i++) {
    buffer.Write("  ");
  }
}

void JSONComposer::ComposeString(WriteBuffer &buffer, Str const &string) {
  buffer.Write('"');
  for (auto const &chr : string) {
    buffer.Write(ParserBase::Escape(chr));
  }
  buffer.Write('"');
}

void JSONComposer::ComposeArray(WriteBuffer &buffer, Array const &array,
                                Size const &indent) {
  buffer.Write('[');
  for (Array::const_iterator begin = array.begin(), end = array.end();
       begin != end; ++begin) {
    this->Indent(mBuffer, indent + 1);
    this->Compose(mBuffer, *begin, indent + 1);
    if (std::next(begin) != end) {
      buffer.Write(", ");
    }
  }
  this->Indent(mBuffer, indent);
  buffer.Write(']');
}

void JSONComposer::ComposeObject(WriteBuffer &buffer, Object const &object,
                                 Size const &indent) {
  buffer.Write('{');
  for (Object::const_iterator begin = object.begin(), end = object.end();
       begin != end; ++begin) {
    this->Indent(mBuffer, indent + 1);
    this->ComposeString(mBuffer, begin->first);
    buffer.Write(": ");
    this->Compose(mBuffer, begin->second, indent + 1);
    if (std::next(begin) != end) {
      buffer.Write(", ");
    }
  }
  this->Indent(mBuffer, indent);
  buffer.Write('}');
}

void JSONComposer::Compose(WriteBuffer &buffer, JSON const &json,
                           Size const &indent) {
  JSONType type = json.GetType();
  switch (type) {
  case JSONType::NULLTYPE:
    buffer.Write("null");
    break;
  case JSONType::BOOLTYPE:
    buffer.Write(json.GetBool() ? "true" : "false");
    break;
  case JSONType::NUMBERTYPE:
    buffer.Write(std::to_string(json.GetNumber()));
    break;
  case JSONType::STRINGTYPE:
    this->ComposeString(buffer, json.GetString());
    break;
  case JSONType::ARRAYTYPE:
    this->ComposeArray(buffer, json.GetArray(), indent);
    break;
  case JSONType::OBJECTTYPE:
    this->ComposeObject(buffer, json.GetObject(), indent);
    break;
  default:
    break;
  }
}
} // namespace TerreateIO::JSON

std::ostream &operator<<(std::ostream &os, TerreateIO::JSON::JSON const &json) {
  TerreateIO::JSON::JSONComposer composer;
  composer.Compose(json);
  os << composer.GetComposed().Dump();
  return os;
}
