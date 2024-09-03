#include "../../includes/model/animation.hpp"
#include "glm/ext/quaternion_common.hpp"

namespace TerreateIO::Model {
using namespace TerreateIO::Defines;
using namespace TerreateCore::Math;

Frame JointAnimation::operator[](Double const &time) const {
  if (time < mFrames[0]) {
    return {mFrames[0], mTransforms[0]};
  }
  if (time > mFrames[mFrames.size() - 1]) {
    return {mFrames[mFrames.size() - 1], mTransforms[mFrames.size() - 1]};
  }

  Uint index = 0;
  for (Uint i = 0; i < mFrames.size(); ++i) {
    if (mFrames[i] > time) {
      index = i;
      break;
    }
  }

  Double t =
      (time - mFrames[index - 1]) / (mFrames[index] - mFrames[index - 1]);
  Transform transform;
  switch (mInterpolationType) {
  case InterpolationType::LINEAR:
    return Animation::Linear({mFrames[index - 1], mTransforms[index - 1]},
                             {mFrames[index], mTransforms[index]}, t);
  case InterpolationType::STEP:
    return Animation::Step({mFrames[index - 1], mTransforms[index - 1]},
                           {mFrames[index], mTransforms[index]}, t);
  default:
    return {mFrames[index], mTransforms[index]};
  }
}

Frame Animation::Linear(Frame const &a, Frame const &b, Double const &t) {
  Transform transform;
  transform.scale =
      a.transform.scale + (b.transform.scale - a.transform.scale) * (Float)t;
  transform.rotation =
      slerp(a.transform.rotation, b.transform.rotation, (Float)t);
  transform.translation =
      a.transform.translation +
      (b.transform.translation - a.transform.translation) * (Float)t;
  return {a.time + (b.time - a.time) * t, transform};
}
} // namespace TerreateIO::Model
