#include <peppermint/classes/rendering/Mesh.h>

#include <glad/glad.h>
#include <string>
#include <peppermint/managers/LogManager.h>
#include <format>

using namespace peppermint::rendering;
using namespace peppermint::managers;
using namespace std;

void Mesh::draw(Shader* shader) {
	shader->use();
	for (unsigned int i = 0; i < this->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		shader->setInt((char*)("material.texture" + std::to_string(i)).c_str(), i);
		this->textures[i].bind();
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