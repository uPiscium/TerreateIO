#ifndef __TERREATEIO_IMPORTER_INTERFACE_HPP__
#define __TERREATEIO_IMPORTER_INTERFACE_HPP__

#include "../container/scene.hpp"
#include "../defines.hpp"

namespace TerreateIO::Core {
using namespace TerreateIO::Defines;
using namespace TerreateIO::Container;

class IImporter : public TerreateObjectBase {
public:
  virtual ~IImporter() = default;
  virtual Str const &GetError() = 0;
  virtual Scene const &GetScene() = 0;
  virtual Bool IsImported() = 0;
  virtual void Import(Str const &path) = 0;
};

} // namespace TerreateIO::Core
#endif // __TERREATEIO_IMPORTER_INTERFACE_HPP__
