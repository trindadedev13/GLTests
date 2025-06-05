#version 300 es
precision mediump float;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 vertex;
in vec2 tex_coord;
in vec4 color;

out vec2 texCoord;
out vec4 vColor;

void main() {
  texCoord = tex_coord;
  vColor = color;
  gl_Position = projection * view * model * vec4(vertex, 1.0);
}