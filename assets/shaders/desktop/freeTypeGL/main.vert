#version 450 core
 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 vertex;
in vec2 tex_coord;
in vec4 color;

out vec2 outTexCoord;
out vec4 outColor;

void main() {
  outTexCoord = tex_coord.xy;
  outColor = color;
  gl_Position = projection*(view*(model*vec4(vertex,1.0)));
}
