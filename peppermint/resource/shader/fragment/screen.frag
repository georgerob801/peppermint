#version 330 core

out vec4 fragColour;

in vec2 uv;

uniform sampler2D screenTexture;

void main() {
	fragColour = texture(screenTexture, uv);
}