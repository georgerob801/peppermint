#ifndef PPMINT_SHADER_H
#define PPMINT_SHADER_H

#include <glm/glm.hpp>

using namespace glm;

namespace peppermint {
	namespace rendering {
		/// <summary>
		/// Class for storing shader information.
		/// </summary>
		class Shader {
		public:
			/// <summary>
			/// The OpenGL ID of this Shader.
			/// </summary>
			unsigned int id;

			/// <summary>
			/// Create a new Shader.
			/// </summary>
			/// <param name="vertexPath">The path to the vertex shader to use. NEEDS TO BE CHANGED TO ASSET</param>
			/// <param name="fragmentPath">The path to the fragment shader to use. NEEDS TO BE CHANGED TO ASSET</param>
			Shader(char* vertexPath, char* fragmentPath);

			/// <summary>
			/// Use this Shader.
			/// </summary>
			void use();
			/// <summary>
			/// Set a uniform bool.
			/// </summary>
			/// <param name="name">The name of the uniform.</param>
			/// <param name="value">The value to set it to.</param>
			void setBool(char* name, bool value) const;
			/// <summary>
			/// Set a uniform int.
			/// </summary>
			/// <param name="name"The name of the uniform.></param>
			/// <param name="value">The value to set it to.</param>
			void setInt(char* name, int value) const;
			/// <summary>
			/// Set a uniform float.
			/// </summary>
			/// <param name="name">The name of the uniform.</param>
			/// <param name="value">The value to set it to.</param>
			void setFloat(char* name, float value) const;
			/// <summary>
			/// Set a uniform mat4.
			/// </summary>
			/// <param name="name">The name of the uniform.</param>
			/// <param name="value">The value to set it to.</param>
			void setMat4f(char* name, mat4 value) const;
			/// <summary>
			/// Set a uniform vec3.
			/// </summary>
			/// <param name="name">The name of the uniform.</param>
			/// <param name="value">The value to set it to.</param>
			void setVec3f(char* name, vec3 value) const;
			/// <summary>
			/// Set a uniform vec2.
			/// </summary>
			/// <param name="name">The name of the uniform.</param>
			/// <param name="value">The value to set it to.</param>
			void setVec2f(char* name, vec2 value) const;
		};
	}
}

#endif