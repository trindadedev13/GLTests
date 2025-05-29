#version 450 core

in vec4 colorOut;
out vec4 fragColor;

void main() {
  fragColor = colorOut;
}