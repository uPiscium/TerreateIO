#ifndef __TERREATEIO_MODEL_CAMERA_HPP__
#define __TERREATEIO_MODEL_CAMERA_HPP__

#include "../defines.hpp"

namespace TerreateIO::Container {
using namespace TerreateIO::Defines;

enum class CameraType { PERSPECTIVE, ORTHOGRAPHIC };

class Camera : public TerreateObjectBase {
private:
  Str mName;
  CameraType mType;
  Pair<Double> mSize;
  Double mNear;
  Double mFar;
  Double mFov;

public:
  Camera()
      : mName("Camera"), mType(CameraType::PERSPECTIVE), mSize({1.0, 1.0}),
        mNear(0.1), mFar(1000.0), mFov(45.0) {}

  Str const &GetName() const { return mName; }
  CameraType const &GetType() const { return mType; }
  Pair<Double> const &GetSize() const { return mSize; }
  Double const &GetWidth() const { return mSize.first; }
  Double const &GetHeight() const { return mSize.second; }
  Double const &GetNear() const { return mNear; }
  Double const &GetFar() const { return mFar; }
  Double const &GetFov() const { return mFov; }

  void SetName(Str const &name) { mName = name; }
  void SetType(CameraType const &type) { mType = type; }
  void SetSize(Pair<Double> const &size) { mSize = size; }
  void SetWidth(Double const &width) { mSize.first = width; }
  void SetHeight(Double const &height) { mSize.second = height; }
  void SetNear(Double const &near) { mNear = near; }
  void SetFar(Double const &far) { mFar = far; }
  void SetFov(Double const &fov) { mFov = fov; }

  Bool IsPerspective() const { return mType == CameraType::PERSPECTIVE; }
  Bool IsOrthographic() const { return mType == CameraType::ORTHOGRAPHIC; }
};
} // namespace TerreateIO::Container

#endif // __TERREATEIO_MODEL_CAMERA_HPP__
