#include "../../includes/model/skeleton.hpp"
#include "../../includes/exceptions.hpp"

namespace TerreateIO::Model {
using namespace TerreateIO::Defines;

void Joint::Initialize(Vec<Joint> &joints, mat4 const &parentOffset) {
  if (mChildIndex != 0u) {
    joints[mChildIndex].Initialize(joints, mOffset);
  }
  if (mSiblingIndex != 0u) {
    joints[mSiblingIndex].Initialize(joints, parentOffset);
  }
  mInitPose = parentOffset * mInitPose;
}

void Joint::Update(Vec<mat4> &transforms, Vec<Joint> &joints,
                   mat4 const &parentPose) {
  mat4 &t = transforms[mIndex];
  t = parentPose * mInitPose * t * mOffset;
  transforms[mIndex] = t;

  if (mChildIndex != 0u) {
    joints[mChildIndex].Update(transforms, joints, t);
  }
  if (mSiblingIndex != 0u) {
    joints[mSiblingIndex].Update(transforms, joints, parentPose);
  }
}

Joint &Joint::operator=(Joint const &joint) {
  mIndex = joint.mIndex;
  mChildIndex = joint.mChildIndex;
  mSiblingIndex = joint.mSiblingIndex;
  mInitPose = joint.mInitPose;
  mOffset = joint.mOffset;
  return *this;
}

Skeleton::Skeleton(Skeleton const &skeleton) {
  mJointTransforms = skeleton.mJointTransforms;
  mJoints = skeleton.mJoints;
}

void Skeleton::Update(Vec<mat4> const &poses) {
  if (poses.size() != mJoints.size()) {
    throw Exception::ModelException("Invalid number of poses");
  }

  for (Uint i = 0; i < mJoints.size(); ++i) {
    mJointTransforms[i] = poses[i];
  }

  mJoints[0].Update(mJointTransforms, mJoints, identity<mat4>());
}

Skeleton &Skeleton::operator=(Skeleton const &skeleton) {
  mJointTransforms = skeleton.mJointTransforms;
  mJoints = skeleton.mJoints;
  return *this;
}
} // namespace TerreateIO::Model
