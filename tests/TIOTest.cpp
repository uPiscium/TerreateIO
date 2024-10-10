#include "../includes/TerreateIO.hpp"
#include "TerreateGraphics/TerreateGraphics.hpp"
#include <iostream>

using namespace TerreateGraphics::Core;
using namespace TerreateGraphics::Compute;
using namespace TerreateIO;

struct Rect {
  Float x0 = 0u;
  Float y0 = 0u;
  Float x1 = 0u;
  Float y1 = 0u;
};

enum class TextureSize {
  S256 = 256,
  S512 = 512,
  S1024 = 1024,
  S2048 = 2048,
  S4096 = 4096
};

class TextureSet final : public TerreateObjectBase {
private:
  GLObject mTexture = GLObject();
  Pair<Uint> mSize = {0u, 0u};
  Pair<FilterType> mFilter = {FilterType::LINEAR, FilterType::LINEAR};
  Pair<WrappingType> mWrap = {WrappingType::REPEAT, WrappingType::REPEAT};
  Map<Str, Uint> mTextures = Map<Str, Uint>();
  Map<Str, Rect> mCoordinates = Map<Str, Rect>();

public:
  TextureSet(Uint const &width, Uint const &height, Uint const &layers = 32);
  TextureSet(TextureSize const &size, Uint const &layers = 32);
  ~TextureSet() override;

  Rect const &GetCoordinates(Str const &name) const {
    return mCoordinates.at(name);
  }

  void SetFilter(FilterType const &min, FilterType const &mag);
  void SetWrapping(WrappingType const &s, WrappingType const &t);

  void LoadData(Str const &name, Uint width, Uint height, Uint channels,
                Ubyte const *data);
  void LoadData(Str const &name, TextureData const &data) {
    this->LoadData(name, data.width, data.height, data.channels,
                   data.pixels.data());
  }

  void Bind() const { glBindTexture(GL_TEXTURE_2D_ARRAY, (TCu32)mTexture); }
  void Unbind() const { glBindTexture(GL_TEXTURE_2D_ARRAY, 0); }
};

TextureSet::TextureSet(Uint const &width, Uint const &height,
                       Uint const &layers)
    : mSize({width, height}) {
  glGenTextures(1, mTexture);

  this->Bind();
  glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA32F, mSize.first, mSize.second,
                 layers);
  this->SetFilter(mFilter.first, mFilter.second);
  this->SetWrapping(mWrap.first, mWrap.second);
  this->Unbind();
}

TextureSet::TextureSet(TextureSize const &size, Uint const &layers)
    : mSize({(Uint)size, (Uint)size}) {
  glGenTextures(1, mTexture);

  this->Bind();
  glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA32F, mSize.first, mSize.second,
                 layers);
  this->SetFilter(mFilter.first, mFilter.second);
  this->SetWrapping(mWrap.first, mWrap.second);
  this->Unbind();
}

TextureSet::~TextureSet() {
  if (mTexture.Count() <= 1) {
    glDeleteTextures(1, mTexture);
    mTexture.Delete();
  }
}

void TextureSet::SetFilter(FilterType const &min, FilterType const &mag) {
  mFilter = {min, mag};
  this->Bind();
  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, (GLenum)min);
  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, (GLenum)mag);
  this->Unbind();
}

void TextureSet::SetWrapping(WrappingType const &s, WrappingType const &t) {
  mWrap = {s, t};
  this->Bind();
  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, (GLenum)s);
  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, (GLenum)t);
  this->Unbind();
}

void TextureSet::LoadData(Str const &name, Uint width, Uint height,
                          Uint channels, Ubyte const *data) {
  mTextures[name] = mTextures.size();
  Rect rect;
  rect.x0 = 0.0f;
  rect.y0 = 0.0f;
  rect.x1 = (float)width / (float)mSize.first;
  rect.y1 = (float)height / (float)mSize.second;
  mCoordinates[name] = rect;
  this->Bind();
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
  glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, mSize.second - height,
                  mTextures[name], width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE,
                  data);
  glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
  this->Unbind();
}

struct Uniform {
  mat4 model;
  mat4 view;
  mat4 proj;
};

class Application {
  Clock mClock;
  Shader mShader;
  mat4 mTransform;
  Float mWidth = 1500.0f;
  Float mHeight = 750.0f;
  Float mNear = 0.01f;
  Float mFar = 10000.0f;
  Float mDepth = mFar - mNear;

  GLTF::GLTFImporter mImporter;

  Buffer mBuffer;

  Uniform mUniform;
  UniformBuffer mUBO;

  TextureSet mTextureSet;

public:
  void SizeCallback(Window *window, int const &width, int const &height) {
    glViewport(0, 0, width, height);
    mWidth = (Float)width;
    mHeight = (Float)height;
    mat4 proj = perspective(45.0f, mWidth / mHeight, mNear, mFar);
    mUniform.proj = proj;
    mUBO.ReloadData(mUniform);
  }

public:
  Application() : mTextureSet(TextureSize::S1024) {
    mShader.AddVertexShaderSource(
        Shader::LoadShaderSource("tests/resources/testVert.glsl"));
    mShader.AddFragmentShaderSource(
        Shader::LoadShaderSource("tests/resources/testFrag.glsl"));
    mShader.Compile();
    mShader.Link();

    mImporter.Import("tests/resources/Cube/Cube.gltf");
    auto &scene = mImporter.GetScene();
    auto &mesh = scene.GetMeshes()[0];
    auto &material = scene.GetMaterials()[0];
    auto binds = material.GetUVBindings();

    int width, height, channels;
    unsigned char *data = stbi_load("tests/resources/Cube/Cube_BaseColor.png",
                                    &width, &height, &channels, 4);
    mTextureSet.LoadData("BASECOLOR", width, height, channels, data);
    stbi_image_free(data);
    data = stbi_load("tests/resources/Cube/Cube_MetallicRoughness.png", &width,
                     &height, &channels, 4);
    mTextureSet.LoadData("METALLICROUGHNESS", width, height, channels, data);
    stbi_image_free(data);

    Rect rect = mTextureSet.GetCoordinates("BASECOLOR");

    BufferDataConstructor constructor;
    for (auto &component : mesh.GetMeshes()[0].GetVertexDataComponents()) {
      constructor.AddVertexComponent(component.first, component.second);
    }

    constructor.SetVertexIndices(
        mesh.GetMeshes()[0].GetVertexConstructionIndices());
    constructor.Construct();

    mBuffer.LoadData(mShader, constructor);
    mBuffer.LoadIndices(mesh.GetMeshes()[0].GetFaceIndices());

    mat4 view = lookAt(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0));
    mat4 proj = perspective(45.0f, mWidth / mHeight, mNear, mFar);
    mUniform.view = view;
    mUniform.proj = proj;
    mUniform.model = identity<mat4>();
    mUBO.LoadData(mUniform);
    mUBO.Bind(mShader, "Matrices");

    mShader.Use();
    mShader.UseDepth(true);
    mShader.SetInt("texArray", 0);
    mShader.ActiveTexture(TextureTargets::TEX_0);
  }

  void OnFrame(Window *window) {
    window->PollEvents();
    window->Fill({0.2, 0.2, 0.2});
    window->Clear();

    Float time = mClock.GetCurrentRuntime() * 10;
    Float angle = radians(time);
    mUniform.model = rotate(identity<mat4>(), angle, vec3(1, 1, 1));
    mUBO.ReloadData(mUniform);

    mShader.Use();
    mTextureSet.Bind();
    mBuffer.Draw(DrawMode::TRIANGLES);
    mTextureSet.Unbind();
    mShader.Unuse();

    window->Swap();
    mClock.Frame(80);
  }
};

int main() {
  Initialize();
  {
    Window window(1500, 750, "TerreateIO Test", WindowSettings());
    Application app;

    window.GetSizePublisher().Subscribe(
        [&app](Window *window, int const &width, int const &height) {
          app.SizeCallback(window, width, height);
        });

    while (window) {
      app.OnFrame(&window);
    }
  }
  Terminate();
  return 0;
}
