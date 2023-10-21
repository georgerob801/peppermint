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
		struct Vertex {
			vec3 position;
			vec2 uv;
		};

		class Mesh {
		public:
			vector<Vertex> vertices;
			vector<unsigned int> indices;
			vector<Texture> textures;

			static vector<Vertex> SQUARE();
			static vector<Vertex> SQUARE(vec3 transform);
			static vector<unsigned int> SQUARE_INDICES();
			static vector<unsigned int> SQUARE_INDICES(unsigned int offset);

			virtual void draw(Shader* shader);
			void setup();
		private:
			// vertex array object
			unsigned int VAO = NULL;
			// vertex buffer object
			unsigned int VBO = NULL;
			// indices (can't remember what it stands for lol)
			unsigned int EBO = NULL;
		};
	}
}

#endif