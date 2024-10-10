#version 330 core
in vec3 iPosition;
in vec3 iUV0;
in vec3 iColor;
in vec3 iNormal;
in vec3 iTangent;

out vec3 vNormal;
out vec3 vUV0;
out vec3 vColor;

layout(std140) uniform Matrices {
  mat4 uModel;
  mat4 uView;
  mat4 uProjection;
};

void main() {
  gl_Position = uProjection * uView * uModel * vec4(iPosition, 1.0f);
  vNormal = iNormal;
  vUV0 = iUV0;
  vColor = iColor;
}
