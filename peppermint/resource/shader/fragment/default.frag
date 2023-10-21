#version 330 core

struct Material {
	sampler2D texture1;
	sampler2D texture2;
	sampler2D texture3;
	sampler2D texture4;
	sampler2D texture5;
	sampler2D texture6;
	sampler2D texture7;
	sampler2D texture8;
};

uniform Material material;

in vec4 position;
in vec2 uv;

out vec4 fragColor;

void main() {
	fragColor = vec4(uv, 0.0f, 1.0f);
}