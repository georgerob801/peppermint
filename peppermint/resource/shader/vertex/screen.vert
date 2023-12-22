#version 330 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inUv;

out vec2 uv;

void main() {
	gl_Position = vec4(inPos.x, inPos.y, 0.0f, 1.0f);
	uv = inUv;
}