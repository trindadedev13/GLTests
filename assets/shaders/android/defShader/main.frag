#version 320 es
precision mediump float;

in vec4 colorOut;

out vec4 fragColor;

void main() {
  fragColor = colorOut;
}