#version 330 core
out vec4 color;

in vec2 texCoord;

uniform sampler2D _texture;

void main() {
  color = texture(_texture, texCoord);
}