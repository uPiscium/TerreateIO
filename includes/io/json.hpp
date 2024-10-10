#ifndef __TERREATEIO_JSON_HPP__
#define __TERREATEIO_JSON_HPP__

#include "constants/json.hpp"
#include "interface.hpp"

namespace TerreateIO::JSON {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Core;

class JSON;

typedef Vec<JSON> Array;
typedef Map<Str, JSON> Object;

namespace Utils {
template <typename T>
concept number = std::is_arithmetic_v<T>;

Bool Extract(JSON const &json, Str const &key, JSON &value);
Bool Extract(JSON const &json, Str const &key, Bool &value);
Bool Extract(JSON const &json, Str const &key, Double &value);
Bool Extract(JSON const &json, Str const &key, Str &value);
Bool Extract(JSON const &json, Str const &key, Array &value);
Bool Extract(JSON const &json, Str const &key, Object &value);

Bool Extract(JSON const &json, Str const &key, Vec<Bool> &value);
Bool Extract(JSON const &json, Str const &key, Vec<Double> &value);
Bool Extract(JSON const &json, Str const &key, Vec<Str> &value);

Bool Extract(JSON const &json, Str const &key, Map<Str, Bool> &value);
Bool Extract(JSON const &json, Str const &key, Map<Str, Double> &value);
Bool Extract(JSON const &json, Str const &key, Map<Str, Str> &value);

template <enumtype T> Bool Extract(JSON const &json, Str const &key, T &value);
template <number T> Bool Extract(JSON const &json, Str const &key, T &value);
template <number T>
Bool Extract(JSON const &json, Str const &key, Vec<T> &value);
template <number T>
Bool Extract(JSON const &json, Str const &key, Nullable<T> &value);
template <number T>
Bool Extract(JSON const &json, Str const &key, Map<Str, T> &value);
template <typename T>
Bool Extract(JSON const &json, Str const &key, Nullable<T> &value);

Str JSONTypeToString(JSONType const &type);

template <enumtype T> Bool Extract(JSON const &json, Str const &key, T &value) {
  Double temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  value = static_cast<T>(temp);
  return true;
}

template <number T> Bool Extract(JSON const &json, Str const &key, T &value) {
  Double temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  value = static_cast<T>(temp);
  return true;
}

template <number T>
Bool Extract(JSON const &json, Str const &key, Vec<T> &value) {
  Vec<Double> temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  value.resize(temp.size());
  for (Uint i = 0; i < temp.size(); ++i) {
    value[i] = static_cast<T>(temp[i]);
  }

  return true;
}

template <number T>
Bool Extract(JSON const &json, Str const &key, Nullable<T> &value) {
  T temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  value = temp;
  return true;
}

template <number T>
Bool Extract(JSON const &json, Str const &key, Map<Str, T> &value) {
  Map<Str, Double> temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  for (auto const &[k, v] : temp) {
    value.insert({k, static_cast<T>(v)});
  }

  return true;
}

template <typename T>
Bool Extract(JSON const &json, Str const &key, Nullable<T> &value) {
  T temp;
  if (!Extract(json, key, temp)) {
    return false;
  }

  value = temp;
  return true;
}
} // namespace Utils

union JSONValue {
  Bool boolean;
  Double number;
  Str *string;
  Array *array;
  Object *object;
};

class JSON {
private:
  JSONValue mValue;
  JSONType mType;

private:
  void Copy(JSON const &json);
  void Clear();

public:
  JSON() : mType(JSONType::NULLTYPE) { mValue.number = 0; }
  explicit JSON(Bool boolean) : mType(JSONType::BOOLTYPE) {
    mValue.boolean = boolean;
  }
  explicit JSON(Double number) : mType(JSONType::NUMBERTYPE) {
    mValue.number = number;
  }
  explicit JSON(Str const &string) : mType(JSONType::STRINGTYPE) {
    mValue.string = new Str(string);
  }
  explicit JSON(Array const &array) : mType(JSONType::ARRAYTYPE) {
    mValue.array = new Array(array);
  }
  explicit JSON(Object const &object) : mType(JSONType::OBJECTTYPE) {
    mValue.object = new Object(object);
  }
  JSON(JSON const &json);
  ~JSON() { this->Clear(); }

  JSONType const &GetType() const { return mType; }
  JSONValue const &GetValue() const { return mValue; }

  Size GetSize() const;
  Vec<Str> GetKeys() const;
  Array GetValues() const;
  Bool const &GetBool() const;
  Double const &GetNumber() const;
  Str const &GetString() const;
  Array const &GetArray() const;
  Object const &GetObject() const;

  Bool IsNull() const { return mType == JSONType::NULLTYPE; }
  Bool IsBool() const { return mType == JSONType::BOOLTYPE; }
  Bool IsNumber() const { return mType == JSONType::NUMBERTYPE; }
  Bool IsString() const { return mType == JSONType::STRINGTYPE; }
  Bool IsArray() const { return mType == JSONType::ARRAYTYPE; }
  Bool IsObject() const { return mType == JSONType::OBJECTTYPE; }

  Bool Has(Str const &key) const;

  JSON &operator[](Size const &index);
  JSON &operator[](Str const &key);
  JSON const &operator[](Size const &index) const;
  JSON const &operator[](Str const &key) const;

  JSON &operator=(Bool const &boolean);
  JSON &operator=(Double const &number);
  JSON &operator=(Str const &string);
  JSON &operator=(Array const &array);
  JSON &operator=(Object const &object);
  JSON &operator=(JSON const &JSON);

  explicit operator Bool() const { return this->GetBool(); }
  explicit operator Double() const { return this->GetNumber(); }
  explicit operator Str() const { return this->GetString(); }
  explicit operator Array() const { return this->GetArray(); }
  explicit operator Object() const { return this->GetObject(); }
};

class JSONParser : public ParserBase {
private:
  JSON mRoot = JSON();

private:
  Bool ParseNull(ReadBuffer &buffer, JSON &json);
  Bool ParseBool(ReadBuffer &buffer, JSON &json);
  Bool ParseNumber(ReadBuffer &buffer, JSON &json);
  Bool ParseString(ReadBuffer &buffer, JSON &json);
  Bool ParseArray(ReadBuffer &buffer, JSON &json);
  Bool ParseObject(ReadBuffer &buffer, JSON &json);

public:
  JSONParser() = default;
  JSONParser(Str const &filepath) : ParserBase(filepath) {}
  ~JSONParser() override = default;

  JSON const &GetRoot() const { return mRoot; }

  Bool Parse(ReadBuffer &buffer) override;
  Bool Parse() override;
};

class JSONComposer : public ComposerBase {
private:
  void Indent(WriteBuffer &buffer, Size const &indent);
  void ComposeString(WriteBuffer &buffer, Str const &string);
  void ComposeArray(WriteBuffer &buffer, Array const &array,
                    Size const &indent);
  void ComposeObject(WriteBuffer &buffer, Object const &object,
                     Size const &indent);

public:
  JSONComposer() = default;
  JSONComposer(Str const &filepath) : ComposerBase(filepath) {}
  ~JSONComposer() override = default;

  void Compose(WriteBuffer &buffer, JSON const &json, Size const &indent);
  void Compose(JSON const &json) { this->Compose(mBuffer, json, 0); }
};
} // namespace TerreateIO::JSON

std::ostream &operator<<(std::ostream &os, TerreateIO::JSON::JSON const &json);

#endif // __TERREATEIO_JSON_HPP__
