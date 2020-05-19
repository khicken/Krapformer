#version 330 core
out vec4 FragColor;

in vec3 outColor; // input from vertex shader
in vec2 texCoords;

uniform sampler2D texture1; // 2d texture is a uniform
uniform sampler2D texture2;

void main() {
    FragColor = texture(texture1, texCoords) * vec4(outColor, 0.2);
}