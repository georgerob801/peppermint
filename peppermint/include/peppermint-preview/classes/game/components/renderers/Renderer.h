#ifndef PPMINT_COMPONENT_RENDERER_H
#define PPMINT_COMPONENT_RENDERER_H

#include <peppermint-preview/classes/game/Component.h>
#include <vector>
#include <peppermint-preview/classes/rendering/Mesh.h>
#include <peppermint-preview/classes/rendering/Texture.h>

using namespace peppermint::rendering;

namespace peppermint {
	namespace game {
		namespace components {
			/// <summary>
			/// Component that allows stuff to be drawn to the screen.
			/// </summary>
			class Renderer : public Component {
			public:
				/// <summary>
				/// Create a new Renderer componenet.
				/// </summary>
				Renderer() {
					this->type = Component::RENDERER;
				}

				/// <summary>
				/// Delete a Renderer component.
				/// </summary>
				~Renderer();

				/// <summary>
				/// A vector containing all the vertices this component draws.
				/// </summary>
				vector<peppermint::rendering::Vertex> vertices;
				/// <summary>
				/// A vector containing pointers to all the textures this component uses.
				/// </summary>
				vector<peppermint::rendering::Texture*> textures;

				/// <summary>
				/// True/false depending on whether the mesh data of this component requires regeneration.
				/// </summary>
				bool requiresRemeshing = false;
				/// <summary>
				/// Generates a mesh for this component if either a mesh hasn't been generated yet, or this component required remeshing.
				/// </summary>
				/// <returns>A pointer to the generated/cached Mesh.</returns>
				Mesh* getOrGenerateMesh();
				/// <summary>
				/// Generates a mesh for this component.
				/// </summary>
				/// <returns>A pointer to the generated Mesh.</returns>
				Mesh* generateMesh();

				/// <summary>
				/// The type of OpenGL buffer to use.
				/// </summary>
				unsigned int bufferType = 0x88E4;

				Mesh::MeshType meshType = Mesh::DEFAULT;

				vec3 vertexColour = vec3(1.0f, 1.0f, 1.0f);
			private:
				/// <summary>
				/// The last Mesh calculated for this component.
				/// </summary>
				Mesh* cachedMesh = nullptr;
			};
		}
	}
}

#endif