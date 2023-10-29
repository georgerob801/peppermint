#ifndef PPMINT_SHADER_H
#define PPMINT_SHADER_H

#include <glm/glm.hpp>

using namespace glm;

namespace peppermint {
	namespace rendering {
		class Shader {
		public:
			unsigned int id;

			Shader(char* vertexPath, char* fragmentPath);

			void use();
			void setBool(char* name, bool value) const;
			void setInt(char* name, int value) const;
			void setFloat(char* name, float value) const;
			void setMat4f(char* name, mat4 value) const;
			void setVec3f(char* name, vec3 value) const;
			void setVec2f(char* name, vec2 value) const;
		};
	}
}

#endif