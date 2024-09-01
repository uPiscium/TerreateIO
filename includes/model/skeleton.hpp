#ifndef __TERREATEIO_MODEL_SKELETON_HPP__
#define __TERREATEIO_MODEL_SKELETON_HPP__

#include "../defines.hpp"

namespace TerreateIO::Model {
using namespace TerreateIO::Defines;
using namespace TerreateCore::Math;

class Joint : public TerreateObjectBase {
private:
  Joint *mChild = nullptr;
  Joint *mSibling = nullptr;

  mat4 *mContainer = nullptr;
  mat4 mInitPose = identity<mat4>();
  mat4 mOffset = identity<mat4>();
  mat4 mTransform = identity<mat4>();

public:
  Joint(mat4 *container, mat4 const &pose, mat4 const &offset);
};

} // namespace TerreateIO::Model

#endif // __TERREATEIO_MODEL_SKELETON_HPP__
