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
		delete this->cachedMesh;
		this->cachedMesh = this->generateMesh();
		return this->cachedMesh;
	}
}

Mesh* Renderer::generateMesh() {
	Mesh* mesh = new Mesh();

	mesh->vertices = this->vertices;

	mesh->indices.clear();
	for (unsigned int i = 0; i < this->vertices.size() / 4; i++) {
		vector<unsigned int> indexPain = Mesh::SQUARE_INDICES(i * 4);
		for (unsigned int j = 0; j < indexPain.size(); j++) {
			mesh->indices.push_back(indexPain[j]);
		}
	}

	mesh->textures = this->textures;

	mesh->setup();

	return mesh;
}