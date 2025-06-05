#version 450 core

in vec2 texCoord;
in vec4 color;

out vec4 outColor;
 
uniform sampler2D texture;

void main() {
  float a = texture2D(texture, texCoord).r;
  outColor = vec4(color.rgb, color.a*a);
}
