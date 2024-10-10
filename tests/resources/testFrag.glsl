#version 330 core
in vec3 vNormal;
in vec3 vUV0;
in vec3 vColor;

out vec4 fragColor;

uniform sampler2DArray texArray;

void main() {
  // if (vUV0.x < 0.5f || vUV0.y < 0.5f) {
  //   fragColor = texture(texArray, vec3(vUV0, 0));
  // } else {
  //   fragColor = texture(texArray, vec3(vUV0 - vec2(0.5f, 0.5f), 1));
  // }
  fragColor = texture(texArray, vUV0) + vec4(0.5f);
}
