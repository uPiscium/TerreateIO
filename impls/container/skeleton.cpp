#include "../../includes/container/skeleton.hpp"
#include "../../includes/exceptions.hpp"

namespace TerreateIO::Container {
using namespace TerreateIO::Defines;
using namespace TerreateCore::Math;

void Joint::Initialize(Vec<Joint> &joints, mat4 const &parentOffset) {
  if (mChild != 0u) {
    joints[mChild].Initialize(joints, mOffset);
  }
  if (mSibling != 0u) {
    joints[mSibling].Initialize(joints, parentOffset);
  }
}

void Joint::Update(Vec<mat4> &transformContainer,
                   Vec<mat4> const &animationFrame, Vec<Joint> &joints,
                   mat4 const &parentPose) {
  mat4 const &transform = animationFrame[mIndex];
  transformContainer[mIndex] = parentPose * mInitPose * transform * mOffset;
}

Joint &Joint::operator=(Joint const &other) {
  mIndex = other.mIndex;
  mChild = other.mChild;
  mSibling = other.mSibling;
  mOffset = other.mOffset;
  mInitPose = other.mInitPose;
  mPose = other.mPose;
  return *this;
}

Vec<mat4> Skeleton::Update(Vec<mat4> const &animationFrame) {
  if (animationFrame.size() != mJoints.size()) {
    throw Exception::ContainerException("Invalid number of poses");
  }

  Vec<mat4> transforms(mJoints.size());
  mJoints[0].Update(transforms, animationFrame, mJoints);
  return transforms;
}
} // namespace TerreateIO::Container
