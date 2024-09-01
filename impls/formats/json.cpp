#include "../../includes/formats/json.hpp"
#include "../../includes/exceptions.hpp"

namespace TerreateIO::JSON {
using namespace TerreateIO::Defines;

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
    json = JSON(std::stod(number));
  } else {
    json = JSON((Double)std::stoll(number));
  }

  return true;
}

Bool JSONParser::ParseString(ReadBuffer &buffer, JSON &json) {
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
  json = JSON(string);
  return true;
}

Bool JSONParser::ParseArray(ReadBuffer &buffer, JSON &json) {
  if (buffer.Peek() != '[') {
    return false;
  }

  buffer.Skip(); // Skip the opening bracket
  Array array;
  while (buffer.Peek() != ']') {
    buffer.SkipWhitespace();
    JSONParser parser;
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
  json = JSON(array);
  return true;
}

Bool JSONParser::ParseObject(ReadBuffer &buffer, JSON &json) {
  if (buffer.Peek() != '{') {
    return false;
  }

  buffer.Skip(); // Skip the opening brace
  Object object;
  while (buffer.Peek() != '}') {
    buffer.SkipWhitespace();
    JSON key;
    if (!this->ParseString(buffer, key)) {
      return false;
    }

    buffer.SkipWhitespace();
    if (buffer.Read() != ":") {
      return false;
    }

    buffer.SkipWhitespace();
    JSONParser parser;
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
  json = JSON(object);
  return true;
}

Bool JSONParser::Parse(ReadBuffer &buffer) {
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
