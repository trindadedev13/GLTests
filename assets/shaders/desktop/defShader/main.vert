#version 450 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

layout(location=0) in vec3 vertexIn;
layout(location=1) in vec4 colorIn;

out vec4 colorOut;

void main() {
  gl_Position = projection * view * model * vec4(vertexIn, 1.0);
  colorOut = colorIn;
}