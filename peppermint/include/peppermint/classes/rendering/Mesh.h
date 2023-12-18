#ifndef PPMINT_MESH_H
#define PPMINT_MESH_H

#include <glm/glm.hpp>
#include <vector>

#include <peppermint/classes/rendering/Shader.h>
#include <peppermint/classes/rendering/Texture.h>

using namespace glm;
using namespace std;

namespace peppermint {
	namespace rendering {
		/// <summary>
		/// Struct for storing vertex information.
		/// </summary>
		struct Vertex {
			/// <summary>
			/// The position of this vertex.
			/// </summary>
			vec3 position;
			/// <summary>
			/// The UV coordinates of this vertex.
			/// </summary>
			vec2 uv;
		};

		/// <summary>
		/// Class for storing mesh information.
		/// </summary>
		class Mesh {
		public:
			/// <summary>
			/// Vector containing all vertices that make up this mesh.
			/// </summary>
			vector<Vertex> vertices;
			/// <summary>
			/// Vector containing all indices that make up this mesh.
			/// </summary>
			vector<unsigned int> indices;
			/// <summary>
			/// Vector containing pointers to all textures that this mesh uses.
			/// </summary>
			vector<Texture*> textures;

			/// <summary>
			/// Destroy this Mesh.
			/// </summary>
			~Mesh();

			/// <summary>
			/// Generate vertices in a square shape.
			/// </summary>
			/// <returns>A vector of vertices in a square.</returns>
			static vector<Vertex> SQUARE();
			/// <summary>
			/// Generate vertices in a square shape in a certain position.
			/// </summary>
			/// <param name="transform">The position to offset the square by.</param>
			/// <returns>A vector of vertices in a square.</returns>
			static vector<Vertex> SQUARE(vec3 transform);
			/// <summary>
			/// Generate the indices for a square.
			/// </summary>
			/// <returns>A vector of the indices for a square.</returns>
			static vector<unsigned int> SQUARE_INDICES();
			/// <summary>
			/// Generate the indices for a square with a certain offset.
			/// </summary>
			/// <param name="offset">The number to offset the indices by.</param>
			/// <returns>A vector of the indices for a square.</returns>
			static vector<unsigned int> SQUARE_INDICES(unsigned int offset);

			/// <summary>
			/// Draw this Mesh.
			/// </summary>
			/// <param name="shader">A pointer to the Shader to use.</param>
			virtual void draw(Shader* shader);
			/// <summary>
			/// Set this Mesh up.
			/// </summary>
			void setup();
			/// <summary>
			/// Set this Mesh up.
			/// </summary>
			/// <param name="VBOtype">The type of VBO to use.</param>
			void setup(unsigned int VBOtype);

			enum MeshType {
				DEFAULT,
				TEXT
			};

			MeshType type = DEFAULT;

			vec3 vertColour = vec3(0.0f, 1.0f, 0.0f);
		private:
			/// <summary>
			/// Index of this Mesh's vertex array object.
			/// </summary>
			unsigned int VAO = NULL;
			/// <summary>
			/// Index of this Mesh's vertex buffer object.
			/// </summary>
			unsigned int VBO = NULL;
			/// <summary>
			/// Index of this Mesh's element buffer object.
			/// </summary>
			unsigned int EBO = NULL;
		};
	}
}

#endif