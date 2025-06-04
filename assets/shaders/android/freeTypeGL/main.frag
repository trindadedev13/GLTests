#version 300 es
precision mediump float;

in vec2 texCoord;
in vec4 vColor;

out vec4 outColor;

uniform sampler2D tex;

void main() {
  float a = texture(tex, texCoord).r;
  outColor = vec4(vColor.rgb, vColor.a * a);
}