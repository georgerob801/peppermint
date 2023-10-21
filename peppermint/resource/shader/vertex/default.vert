#version 330 core

layout (location = 0) in vec3 positionIn;
layout (location = 1) in vec2 uvIn;

out vec4 position;
out vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	position = vec4(positionIn * 0.3, 1.0);
	uv = uvIn;
	gl_Position = position;
}