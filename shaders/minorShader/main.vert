#version 450

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

in layout(location=0) vec3 vertexIn;
in layout(location=1) vec4 colorIn;

out vec4 colorOut;

void main() {
  gl_Position = projection * view * model * vec4(vertexIn, 1.0);
  colorOut = colorIn;
}