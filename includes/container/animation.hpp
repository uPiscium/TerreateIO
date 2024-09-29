#ifndef __TERREATEIO_MODEL_ANIMATION_HPP__
#define __TERREATEIO_MODEL_ANIMATION_HPP__

#include "../defines.hpp"

namespace TerreateIO::Container {
using namespace TerreateIO::Defines;
using namespace TerreateCore::Math;

struct Transform {
  vec3 scale;
  quat rotation;
  vec3 translation;
};

struct Frame {
  Double time;
  Transform transform;
};

class JointAnimation : public TerreateObjectBase {
private:
  InterpolationType mInterpolationType;
  Vec<Double> mFrames;
  Vec<Transform> mTransforms;

public:
  JointAnimation() = default;
  JointAnimation(InterpolationType const &type, Vec<Double> const &frames,
                 Vec<Transform> const &transforms)
      : mInterpolationType(type), mFrames(frames), mTransforms(transforms) {}

  Uint GetFrameCount() const { return mFrames.size(); }
  Double const &GetFrame(Uint const &index) const { return mFrames[index]; }
  Double &GetFrame(Uint const &index) { return mFrames[index]; }
  Transform const &GetTransform(Uint const &index) const {
    return mTransforms[index];
  }
  Transform &GetTransform(Uint const &index) { return mTransforms[index]; }

  Frame operator[](Uint const &index) const {
    return {mFrames[index], mTransforms[index]};
  }
  Frame operator[](Double const &time) const;
};

class Animation : public TerreateObjectBase {
private:
  Str mName;
  Vec<JointAnimation> mJointAnimations;

public:
  Animation() = default;

  Uint GetJointCount() const { return mJointAnimations.size(); }
  JointAnimation const &GetJointAnimation(Uint const &index) const {
    return mJointAnimations[index];
  }
  JointAnimation &GetJointAnimation(Uint const &index) {
    return mJointAnimations[index];
  }

  void AddJointAnimation(JointAnimation const &jointAnimation) {
    mJointAnimations.push_back(jointAnimation);
  }

  JointAnimation operator[](Uint const &index) const {
    return mJointAnimations[index];
  }
  Vec<Frame> operator[](Double const &time) const;

public:
  static Frame Linear(Frame const &a, Frame const &b, Double const &t);
  static Frame Step(Frame const &a, Frame const &b, Double const &t) {
    return t < 0.5 ? a : b;
  }
};
} // namespace TerreateIO::Container

#endif // __TERREATEIO_MODEL_ANIMATION_HPP__
