#include <peppermint/classes/game/components/renderers/Renderer.h>

using namespace peppermint::game::components;

#include <iostream>
Renderer::~Renderer() {
	delete this->cachedMesh;
}

Mesh* Renderer::getOrGenerateMesh() {
	if (!this->requiresRemeshing && this->cachedMesh != NULL) {
		return this->cachedMesh;
	} else {
		this->cachedMesh = this->generateMesh();
		this->requiresRemeshing = false;
		return this->cachedMesh;
	}
}

Mesh* Renderer::generateMesh() {
	Mesh* mesh;
	if (this->cachedMesh == nullptr) mesh = new Mesh();
	else mesh = this->cachedMesh;

	mesh->type = this->meshType;

	mesh->vertices.clear();
	vector<Vertex>().swap(mesh->vertices);
	mesh->vertices = this->vertices;

	mesh->indices.clear();
	for (unsigned int i = 0; i < this->vertices.size() / 4; i++) {
		vector<unsigned int> indexPain = Mesh::SQUARE_INDICES(i * 4);
		for (unsigned int j = 0; j < indexPain.size(); j++) {
			mesh->indices.push_back(indexPain[j]);
		}
	}

	mesh->textures = this->textures;

	mesh->setup(this->bufferType);

	mesh->vertColour = this->vertexColour;

	return mesh;
}