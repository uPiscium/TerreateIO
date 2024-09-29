#ifndef __TERREATEIO_SKELETON_HPP__
#define __TERREATEIO_SKELETON_HPP__

#include "../defines.hpp"

namespace TerreateIO::Container {
using namespace TerreateIO::Defines;
using namespace TerreateCore::Math;

class Joint : public TerreateObjectBase {
private:
  Uint mIndex = 0u;
  Uint mChild = 0u;
  Uint mSibling = 0u;
  mat4 mOffset = identity<mat4>();
  mat4 mInitPose = identity<mat4>();
  mat4 mPose = identity<mat4>();

public:
  Joint() = default;
  ~Joint() = default;

  vec3 AcquireFront() const { return vec3(mPose * vec4(0, 1, 0, 0)); }

  void SetInitPose(mat4 const &pose) { mInitPose = pose; }
  void SetOffset(mat4 const &offset) { mOffset = offset; }

  void Initialize(Vec<Joint> &joints,
                  mat4 const &parentOffset = identity<mat4>());
  void Update(Vec<mat4> &transformContainer, Vec<mat4> const &animationFrame,
              Vec<Joint> &joints, mat4 const &parentPose = identity<mat4>());

  Joint &operator=(Joint const &other);
};

class Skeleton : public TerreateObjectBase {
private:
  Vec<Joint> mJoints;
  Vec<Uint> mStructure;

public:
  Skeleton() = default;
  ~Skeleton() = default;

  Vec<mat4> Update(Vec<mat4> const &animationFrame);
};
} // namespace TerreateIO::Container

#endif // __TERREATEIO_SKELETON_HPP__
