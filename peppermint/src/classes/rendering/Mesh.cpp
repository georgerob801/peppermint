#include <peppermint/classes/rendering/Mesh.h>

#include <glad/glad.h>
#include <string>
#include <peppermint/managers/LogManager.h>
#include <format>

using namespace peppermint::rendering;
using namespace peppermint::managers;
using namespace std;

Mesh::~Mesh() {
	glDeleteBuffers(1, &this->EBO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->VAO);
}

vector<Vertex> Mesh::SQUARE() {
	vector<Vertex> out;
	Vertex vert1 = {
		.position = vec3(0.0f, 0.0f, 0.0f),
		.uv = vec2(0.0f, 0.0f)
	};
	Vertex vert2 = {
		.position = vec3(1.0f, 0.0f, 0.0f),
		.uv = vec2(1.0f, 0.0f)
	};
	Vertex vert3 = {
		.position = vec3(0.0f, 1.0f, 0.0f),
		.uv = vec2(0.0f, 1.0f)
	};
	Vertex vert4 = {
		.position = vec3(1.0f, 1.0f, 0.0f),
		.uv = vec2(1.0f, 1.0f)
	};

	out.push_back(vert1);
	out.push_back(vert2);
	out.push_back(vert3);
	out.push_back(vert4);

	return out;
}

vector<Vertex> Mesh::SQUARE(vec3 transform) {
	vector<Vertex> out;
	Vertex vert1 = {
		.position = vec3(0.0f, 0.0f, 0.0f) + transform,
		.uv = vec2(0.0f, 0.0f)
	};
	Vertex vert2 = {
		.position = vec3(1.0f, 0.0f, 0.0f) + transform,
		.uv = vec2(1.0f, 0.0f)
	};
	Vertex vert3 = {
		.position = vec3(0.0f, 1.0f, 0.0f) + transform,
		.uv = vec2(0.0f, 1.0f)
	};
	Vertex vert4 = {
		.position = vec3(1.0f, 1.0f, 0.0f) + transform,
		.uv = vec2(1.0f, 1.0f)
	};

	out.push_back(vert1);
	out.push_back(vert2);
	out.push_back(vert3);
	out.push_back(vert4);

	return out;
}

vector<unsigned int> Mesh::SQUARE_INDICES() {
	return vector<unsigned int> {
		0, 1, 2, 1, 3, 2
	};
};

vector<unsigned int> Mesh::SQUARE_INDICES(unsigned int offset) {
	return vector<unsigned int> {
		0 + offset, 1 + offset, 2 + offset, 1 + offset, 3 + offset, 2 + offset
	};
};

void Mesh::draw(Shader* shader) {
	shader->use();
	for (unsigned int i = 0; i < this->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		shader->setInt((char*)("material.texture" + std::to_string(i)).c_str(), i);
		this->textures[i]->bind();
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, (unsigned int)(this->indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setup() {
	LogManager::debug("Setting up buffers");
	glGenVertexArrays(1, &this->VAO);
	LogManager::debug(format("Created VAO at {}", this->VAO));
	glGenBuffers(1, &this->VBO);
	LogManager::debug(format("Created VBO at {}", this->VBO));
	glGenBuffers(1, &this->EBO);
	LogManager::debug(format("Created EBO at {}", this->EBO));

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// uv
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}