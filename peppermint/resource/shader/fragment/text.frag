#version 330 core

in vec2 uv;
out vec4 fragColour;

uniform sampler2D text;
uniform vec3 vertexColour;

void main() {
	vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(text, uv).r);
	fragColour = vec4(vertexColour, 1.0f) * sampled;
}