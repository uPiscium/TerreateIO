#ifndef __TERREATEIO_JSON_HPP__
#define __TERREATEIO_JSON_HPP__

#include "buffer.hpp"
#include "composer.hpp"
#include "defines.hpp"
#include "parser.hpp"

namespace TerreateIO::Json {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;

class Json;

typedef Vec<Json> Array;
typedef Map<Str, Json> Object;

enum class JsonType {
  NULLTYPE,
  BOOLTYPE,
  NUMBERTYPE,
  STRINGTYPE,
  ARRAYTYPE,
  OBJECTTYPE
};

Str JsonTypeToString(JsonType const &type);

union JsonValue {
  Bool boolean;
  Double number;
  Str *string;
  Array *array;
  Object *object;
};

class Json {
private:
  JsonValue mValue;
  JsonType mType;

private:
  void Copy(Json const &json);
  void Clear();

public:
  Json() : mType(JsonType::NULLTYPE) { mValue.number = 0; }
  explicit Json(Bool boolean) : mType(JsonType::BOOLTYPE) {
    mValue.boolean = boolean;
  }
  explicit Json(Double number) : mType(JsonType::NUMBERTYPE) {
    mValue.number = number;
  }
  explicit Json(Str const &string) : mType(JsonType::STRINGTYPE) {
    mValue.string = new Str(string);
  }
  explicit Json(Array const &array) : mType(JsonType::ARRAYTYPE) {
    mValue.array = new Array(array);
  }
  explicit Json(Object const &object) : mType(JsonType::OBJECTTYPE) {
    mValue.object = new Object(object);
  }
  Json(Json const &json);
  ~Json() { this->Clear(); }

  JsonType const &GetType() const { return mType; }
  JsonValue const &GetValue() const { return mValue; }

  Size GetSize() const;
  Bool const &GetBool() const;
  Double const &GetNumber() const;
  Str const &GetString() const;
  Array const &GetArray() const;
  Object const &GetObject() const;

  Bool IsNull() const { return mType == JsonType::NULLTYPE; }
  Bool IsBool() const { return mType == JsonType::BOOLTYPE; }
  Bool IsNumber() const { return mType == JsonType::NUMBERTYPE; }
  Bool IsString() const { return mType == JsonType::STRINGTYPE; }
  Bool IsArray() const { return mType == JsonType::ARRAYTYPE; }
  Bool IsObject() const { return mType == JsonType::OBJECTTYPE; }

  Bool Has(Str const &key) const;

  Json &operator[](Size const &index);
  Json &operator[](Str const &key);
  Json const &operator[](Size const &index) const;
  Json const &operator[](Str const &key) const;

  Json &operator=(Bool const &boolean);
  Json &operator=(Double const &number);
  Json &operator=(Str const &string);
  Json &operator=(Array const &array);
  Json &operator=(Object const &object);
  Json &operator=(Json const &json);

  explicit operator Bool() const { return this->GetBool(); }
  explicit operator Double() const { return this->GetNumber(); }
  explicit operator Str() const { return this->GetString(); }
  explicit operator Array() const { return this->GetArray(); }
  explicit operator Object() const { return this->GetObject(); }
};

class JsonParser : public ParserBase {
private:
  Json mRoot = Json();

private:
  Bool ParseNull(Buffer::ReadBuffer &buffer, Json &json);
  Bool ParseBool(Buffer::ReadBuffer &buffer, Json &json);
  Bool ParseNumber(Buffer::ReadBuffer &buffer, Json &json);
  Bool ParseString(Buffer::ReadBuffer &buffer, Json &json);
  Bool ParseArray(Buffer::ReadBuffer &buffer, Json &json);
  Bool ParseObject(Buffer::ReadBuffer &buffer, Json &json);

public:
  JsonParser() = default;
  JsonParser(Str const &filepath) : ParserBase(filepath) {}
  ~JsonParser() override = default;

  Json const &GetRoot() const { return mRoot; }

  Bool Parse(Buffer::ReadBuffer &buffer) override;
  Bool Parse() override;
};

class JsonComposer : public ComposerBase {
private:
  void Indent(Buffer::WriteBuffer &buffer, Size const &indent);
  void ComposeString(Buffer::WriteBuffer &buffer, Str const &string);
  void ComposeArray(Buffer::WriteBuffer &buffer, Array const &array,
                    Size const &indent);
  void ComposeObject(Buffer::WriteBuffer &buffer, Object const &object,
                     Size const &indent);

public:
  JsonComposer() = default;
  JsonComposer(Str const &filepath) : ComposerBase(filepath) {}
  ~JsonComposer() override = default;

  void Compose(Buffer::WriteBuffer &buffer, Json const &json,
               Size const &indent);
  void Compose(Json const &json) { this->Compose(mBuffer, json, 0); }
};
} // namespace TerreateIO::Json

std::ostream &operator<<(std::ostream &os, TerreateIO::Json::Json const &json);

#endif // __TERREATEIO_JSON_HPP__
