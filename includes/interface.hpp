#ifndef __TERREATEIO_INTERFACE_HPP__
#define __TERREATEIO_INTERFACE_HPP__

#include "defines.hpp"
#include "scene.hpp"

namespace TerreateIO::Core {
using namespace TerreateIO::Defines;

class IImporter : public TerreateObjectBase {
public:
  virtual Scene::Scene const &GetScene() = 0;
  virtual Bool IsImported() = 0;
  virtual void Import(Str const &path) = 0;
};

class IExporter : public TerreateObjectBase {
public:
  virtual Bool IsExported() = 0;
  virtual void Export(Str const &path, Scene::Scene const &scene) = 0;
};

} // namespace TerreateIO::Core
#endif // __TERREATEIO_INTERFACE_HPP__
