#include <peppermint/classes/rendering/Mesh.h>

#include <glad/glad4.h>
#include <string>
#include <peppermint/managers/LogManager.h>
#include <format>

using namespace peppermint::rendering;
using namespace peppermint::managers;
using namespace std;

Mesh::~Mesh() {
	LogManager::debug(format("Deleting EBO at {}", this->EBO));
	glDeleteBuffers(1, &this->EBO);
	LogManager::debug(format("Deleted EBO at {}", this->EBO));
	LogManager::debug(format("Deleting VBO at {}", this->VBO));
	glDeleteBuffers(1, &this->VBO);
	LogManager::debug(format("Deleted VBO at {}", this->VBO));
	LogManager::debug(format("Deleting VAO at {}", this->VAO));
	glDeleteBuffers(1, &this->VAO);
	LogManager::debug(format("Deleted VAO at {}", this->VAO));
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
	switch (this->type) {
	case TEXT:
		// each letter is 6 vertices
		shader->use();
		shader->setInt((char*)"text", 15);
		shader->setVec3f((char*)"textColour", this->vertColour);
		for (unsigned int i = 0; i < (int)std::ceil((float)this->vertices.size() / (float)4); i++) {
			// arbitrarily decided to use slot 15 for text textures
			glActiveTexture(GL_TEXTURE15);
			this->textures[i]->bind();

			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(this->VAO);
			glDrawElements(GL_TRIANGLES, (unsigned int)6, GL_UNSIGNED_INT, (void*)(6 * i * sizeof(unsigned int)));
		}
		glBindVertexArray(0);
		break;
	case DEFAULT:
	default:
		shader->use();
		for (unsigned int i = 0; i < this->textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			shader->setInt((char*)("material.texture" + std::to_string(i)).c_str(), i);
			this->textures[i]->bind();
		}
		glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, (unsigned int)(this->indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void Mesh::setup() {
	this->setup(GL_STATIC_DRAW);
}

void Mesh::setup(unsigned int VBOtype) {
	if (this->VAO == NULL) {
		glGenVertexArrays(1, &this->VAO);
		LogManager::debug(format("Created VAO at {}", this->VAO));
		glBindVertexArray(this->VAO);

		glGenBuffers(1, &this->VBO);
		LogManager::debug(format("Created VBO at {}", this->VBO));
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

		glGenBuffers(1, &this->EBO);
		LogManager::debug(format("Created EBO at {}", this->EBO));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

		glBindVertexArray(this->VAO);
		// position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		// uv
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(1);
	}

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], VBOtype);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], VBOtype);

	glBindVertexArray(0);
}