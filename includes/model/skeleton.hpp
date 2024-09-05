#ifndef __TERREATEIO_MODEL_SKELETON_HPP__
#define __TERREATEIO_MODEL_SKELETON_HPP__

#include "../defines.hpp"

namespace TerreateIO::Model {
using namespace TerreateIO::Defines;
using namespace TerreateCore::Math;

class Joint : public TerreateObjectBase {
private:
  Uint mIndex = 0u;
  Uint mChildIndex = 0u;
  Uint mSiblingIndex = 0u;
  mat4 mInitPose = identity<mat4>();
  mat4 mOffset = identity<mat4>();

public:
  Joint() {}
  Joint(Joint const &joint)
      : mIndex(joint.mIndex), mChildIndex(joint.mChildIndex),
        mSiblingIndex(joint.mSiblingIndex), mInitPose(joint.mInitPose),
        mOffset(joint.mOffset) {}
  ~Joint() {}

  Uint const &GetIndex() const { return mIndex; }
  Uint const &GetChildIndex() const { return mChildIndex; }
  Uint const &GetSiblingIndex() const { return mSiblingIndex; }
  mat4 const &GetInitPose() const { return mInitPose; }
  mat4 const &GetOffset() const { return mOffset; }

  void SetIndex(Uint const &index) { mIndex = index; }
  void SetChildIndex(Uint const &index) { mChildIndex = index; }
  void SetSiblingIndex(Uint const &index) { mSiblingIndex = index; }
  void SetInitPose(mat4 const &pose) { mInitPose = pose; }
  void SetOffset(mat4 const &offset) { mOffset = offset; }

  void Initialize(Vec<Joint> &joints, mat4 const &parentOffset);
  void Update(Vec<mat4> &transforms, Vec<Joint> &joints,
              mat4 const &parentPose);

  Joint &operator=(Joint const &joint);
};

class Skeleton : public TerreateObjectBase {
private:
  Vec<Joint> mJoints;
  Vec<mat4> mJointTransforms;

public:
  Skeleton() {}
  Skeleton(Skeleton const &skeleton);
  ~Skeleton() {}

  Vec<Joint> const &GetJoints() const { return mJoints; }
  Vec<mat4> const &GetJointTransforms() const { return mJointTransforms; }

  void SetJoints(Vec<Joint> const &joints) { mJoints = joints; }

  void Initialize() { mJoints[0].Initialize(mJoints, identity<mat4>()); }
  void Update(Vec<mat4> const &poses);

  Skeleton &operator=(Skeleton const &skeleton);
  mat4 const &operator[](Uint const &index) const {
    return mJointTransforms[index];
  }
  mat4 &operator[](Uint const &index) { return mJointTransforms[index]; }
};

} // namespace TerreateIO::Model

#endif // __TERREATEIO_MODEL_SKELETON_HPP__
