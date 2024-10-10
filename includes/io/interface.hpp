#ifndef __TERREATEIO_IMPORTER_INTERFACE_HPP__
#define __TERREATEIO_IMPORTER_INTERFACE_HPP__

#include "../buffer.hpp"
#include "../container/scene.hpp"
#include "../defines.hpp"

namespace TerreateIO::Core {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Container;

class ParserBase : public TerreateObjectBase {
protected:
  Str mFilePath;
  Str mParent;
  Vec<Str> mPath;

public:
  ParserBase() {}
  ParserBase(Str const &path);
  virtual ~ParserBase() override {}

  Str const &GetFilePath() const { return mFilePath; }
  Str const &GetParent() const { return mParent; }
  Vec<Str> const &GetPath() const { return mPath; }

  virtual Bool Parse(ReadBuffer &buffer) = 0;
  virtual Bool Parse() = 0;

public:
  static ReadBuffer LoadFile(Str const &path);
  static Str Escape(Byte const &chr);
  static Str Unescape(Byte const &chr);
};

class ComposerBase : public TerreateObjectBase {
protected:
  Str mFilePath;
  WriteBuffer mBuffer;

public:
  ComposerBase() {}
  ComposerBase(Str const &path) : mFilePath(path) {}
  virtual ~ComposerBase() override {}

  WriteBuffer const &GetComposed() const { return mBuffer; }
  WriteBuffer &GetComposed() { return mBuffer; }

  template <typename T> void Compose(T const &data) { mBuffer.Write(data); }

public:
  static void SaveFile(Str const &path, WriteBuffer const &buffer);
};

class IImporter : public TerreateObjectBase {
public:
  virtual ~IImporter() = default;
  virtual Str const &GetError() = 0;
  virtual Scene const &GetScene() = 0;
  virtual Bool IsImported() = 0;
  virtual void Import(Str const &path) = 0;
};

class IExporter : public TerreateObjectBase {
public:
  virtual ~IExporter() = default;
  virtual Str const &GetError() = 0;
  virtual Bool IsExported() = 0;
  virtual void Export(Str const &path, Scene const &scene) = 0;
};
} // namespace TerreateIO::Core
#endif // __TERREATEIO_IMPORTER_INTERFACE_HPP__
