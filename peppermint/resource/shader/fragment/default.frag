#version 330 core

struct Material {
	sampler2D texture0;
	sampler2D texture1;
	sampler2D texture2;
	sampler2D texture3;
	sampler2D texture4;
	sampler2D texture5;
	sampler2D texture6;
	sampler2D texture7;

	int useTexture;
	vec2 offset;
};

uniform Material material;

in vec4 position;
in vec2 uv;

out vec4 fragColour;

void main() {
	vec4 texColour;
	switch (material.useTexture) {
	case 0:
		texColour = texture(material.texture0, uv + material.offset);
		break;
	case 1:
		texColour = texture(material.texture1, uv + material.offset);
		break;
	case 2:
		texColour = texture(material.texture2, uv + material.offset);
		break;
	case 3:
		texColour = texture(material.texture3, uv + material.offset);
		break;
	case 4:
		texColour = texture(material.texture4, uv + material.offset);
		break;
	case 5:
		texColour = texture(material.texture5, uv + material.offset);
		break;
	case 6:
		texColour = texture(material.texture6, uv + material.offset);
		break;
	case 7:
		texColour = texture(material.texture7, uv + material.offset);
		break;
	default:
		texColour = texture(material.texture0, uv + material.offset);
		break;
	}

	if (texColour.a < 0.01) discard;
	fragColour = texColour;
}