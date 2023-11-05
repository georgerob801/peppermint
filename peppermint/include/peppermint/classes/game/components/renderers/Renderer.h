#ifndef PPMINT_COMPONENT_RENDERER_H
#define PPMINT_COMPONENT_RENDERER_H

#include <peppermint/classes/game/Component.h>
#include <vector>
#include <peppermint/classes/rendering/Mesh.h>
#include <peppermint/classes/rendering/Texture.h>

using namespace peppermint::rendering;

namespace peppermint {
	namespace game {
		namespace components {
			class Renderer : public Component {
			public:
				Renderer() {
					this->type = Component::RENDERER;
				}

				~Renderer();

				vector<peppermint::rendering::Vertex> vertices;
				vector<peppermint::rendering::Texture*> textures;

				bool requiresRemeshing = false;
				Mesh* getOrGenerateMesh();
				Mesh* generateMesh();
			private:
				Mesh* cachedMesh;
			};
		}
	}
}

#endif