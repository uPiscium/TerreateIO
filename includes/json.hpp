#ifndef __TERREATEIO_JSON_HPP__
#define __TERREATEIO_JSON_HPP__

#include "IOController.hpp"
#include "defines.hpp"
#include "parser.hpp"
#include "stringBuffer.hpp"

namespace TerreateIO::Parser::Json {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Parser;

union JsonValue;

typedef Vec<JsonValue> JsonArray;
typedef Map<Str, JsonValue> JsonObject;

union JsonValue {
  Ubyte null;
  Bool boolean;
  Double number;
  Str *string;
  JsonArray *array;
  JsonObject *object;
};

enum class JsonType {
  NULLTYPE,
  BOOLTYPE,
  NUMBERTYPE,
  STRTYPE,
  ARRAYTYPE,
  OBJECTTYPE
};

class JsonToken final {
private:
  JsonType mType;
  JsonValue mValue;

public:
  JsonToken() : mType(JsonType::NULLTYPE) { mValue.null = (Ubyte)NULL; }
  JsonToken(Bool const &value) : mType(JsonType::BOOLTYPE) {
    mValue.boolean = value;
  }
  JsonToken(Double const &value) : mType(JsonType::NUMBERTYPE) {
    mValue.number = value;
  }
  JsonToken(Str const &value) : mType(JsonType::STRTYPE) {
    mValue.string = new Str(value);
  }
  JsonToken(JsonArray const &value) : mType(JsonType::ARRAYTYPE) {
    mValue.array = new JsonArray(value);
  }
  JsonToken(JsonObject const &value) : mType(JsonType::OBJECTTYPE) {
    mValue.object = new JsonObject(value);
  }
  JsonToken(JsonValue const &value, JsonType const &type);
  JsonToken(JsonToken const &token);
  JsonToken(JsonToken &&token);
  ~JsonToken() { this->Clear(); }

  JsonType GetType() const { return mType; }
  JsonValue GetValue() const { return mValue; }
  Bool const &GetBool() const { return mValue.boolean; }
  Double const &GetNumber() const { return mValue.number; }
  Str const &GetString() const { return *mValue.string; }
  JsonArray const &GetArray() const { return *mValue.array; }
  JsonObject const &GetObject() const { return *mValue.object; }
  JsonValue &GetValue(Str const &key);
  JsonValue &GetValue(Uint const &index);

  Bool const &AcquireBool() const;
  Double const &AcquireNumber() const;
  Str const &AcquireString() const;
  JsonArray const &AcquireArray() const;
  JsonArray &AcquireArray();
  JsonObject const &AcquireObject() const;
  JsonObject &AcquireObject();

  void SetType(JsonType const &type) { mType = type; }
  void SetValue(JsonValue const &value) { mValue = value; }
  void SetValue();
  void SetValue(Bool const &value);
  void SetValue(Double const &value);
  void SetValue(Str const &value);
  void SetValue(JsonArray const &value);
  void SetValue(JsonObject const &value);

  Bool IsNull() const { return mType == JsonType::NULLTYPE; }
  Bool IsBool() const { return mType == JsonType::BOOLTYPE; }
  Bool IsNumber() const { return mType == JsonType::NUMBERTYPE; }
  Bool IsString() const { return mType == JsonType::STRTYPE; }
  Bool IsArray() const { return mType == JsonType::ARRAYTYPE; }
  Bool IsObject() const { return mType == JsonType::OBJECTTYPE; }

  Bool Has(Str const &key) const;
  Size Size() const;
  void Clear();

  JsonValue &operator[](Str const &key) { return this->GetValue(key); }
  JsonValue &operator[](Uint const &index) { return this->GetValue(index); }

  JsonToken &operator=(JsonToken const &token);
  JsonToken &operator=(JsonToken &&token);
  JsonToken &operator=(Bool const &value);
  JsonToken &operator=(Double const &value);
  JsonToken &operator=(Str const &value);
  JsonToken &operator=(JsonArray const &value);
  JsonToken &operator=(JsonObject const &value);

  operator Bool() const { return this->AcquireBool(); }
  operator Double() const { return this->AcquireNumber(); }
  operator Str() const { return this->AcquireString(); }
  operator JsonArray() const { return this->AcquireArray(); }
  operator JsonObject() const { return this->AcquireObject(); }
};

class JsonParser final : public ParserBase {
private:
  JsonToken mRoot;
  Size mMaxDepth;

private:
  JsonType Next();
  Bool ParseNull(JsonToken &token);
  Bool ParseBool(JsonToken &token);
  Bool ParseNumber(JsonToken &token);
  Bool ParseString(JsonToken &token);
  Bool ParseArray(JsonToken &token);
  Bool ParseObject(JsonToken &token);

public:
  JsonParser(Str const &filepath, Size const &maxDepth)
      : ParserBase(filepath), mMaxDepth(maxDepth) {}
  ~JsonParser() {}

  JsonToken const &GetRoot() const { return mRoot; }
  JsonToken &GetRoot() { return mRoot; }

  void Parse() override;
};
} // namespace TerreateIO::Parser::Json

#endif // __TERREATEIO_JSON_HPP__
