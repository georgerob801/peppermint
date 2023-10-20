#include <peppermint/classes/rendering/Shader.h>

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <format>
#include <peppermint/managers/LogManager.h>
#include <peppermint/Exceptions.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace peppermint::rendering;
using namespace peppermint::managers;
using namespace std;

Shader::Shader(char* vertexPath, char* fragmentPath) {
	LogManager::debug(format("Creating a new shader from '{}' and '{}'", vertexPath, fragmentPath));
	// retrieve source code from paths
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	// if stream exception stuff
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	// open 
	try {
		LogManager::debug("Opening files");
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream;
		stringstream fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close files
		vShaderFile.close();
		fShaderFile.close();
		// stream -> string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	} catch (ifstream::failure e) {
		LogManager::error("Failed to open either '{}' or '{}' when creating new shader");
		throw peppermint::exceptions::rendering::shader::CannotOpenFileException();
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// shader pointers
	unsigned int vertex;
	unsigned int fragment;
	int success;
	char infoLog[512];

	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	LogManager::debug(format("Assigned memory for vertex shader at {}", vertex));
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	LogManager::debug(format("Set source code for vertex shader at {}", vertex));
	LogManager::debug(format("Attempting to compile vertex shader at {}", vertex));
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		LogManager::error(format("Failed to compile vertex shader at {}:\n{}", vertex, infoLog));
	} else {
		LogManager::debug(format("Compiled vertex shader at {} successfully", vertex));
	}

	// fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	LogManager::debug(format("Assigned memory for fragment shader at {}", fragment));
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	LogManager::debug(format("Set source code for fragment shader at {}", fragment));
	LogManager::debug(format("Attempting to compile fragment shader at {}", fragment));
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		LogManager::error(format("Failed to compile fragment shader at {}:\n{}", fragment, infoLog));
	} else {
		LogManager::debug(format("Compiled fragment shader at {} successfully", fragment));
	}

	// shader program
	this->id = glCreateProgram();
	LogManager::debug(format("Assigned memory for shader program at {}", this->id));
	glAttachShader(this->id, vertex);
	LogManager::debug(format("Attached vertex shader at {} to shader program at {}", vertex, this->id));
	glAttachShader(this->id, fragment);
	LogManager::debug(format("Attached fragment shader at {} to shader program at {}", fragment, this->id));
	LogManager::debug(format("Attempting to link shader program at {}", this->id));
	glLinkProgram(this->id);
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->id, 512, NULL, infoLog);
		LogManager::error(format("Failed to link shader program at {}:\n{}", this->id, infoLog));
	} else {
		LogManager::debug(format("Linked shader program at {} successfully", this->id));
	}

	LogManager::debug(format("Deleting original shaders at {} and {}", vertex, fragment));
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	LogManager::info(format("Successfully created new shader with files '{}' and '{}'", vertexPath, fragmentPath));
}

void Shader::use() {
	glUseProgram(this->id);
}

void Shader::setBool(char* name, bool value) const {
	glUniform1i(glGetUniformLocation(this->id, name), (int)value);
}

void Shader::setInt(char* name, int value) const {
	glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::setFloat(char* name, float value) const {
	glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::setMat4f(char* name, mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3f(char* name, vec3 value) const {
	glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}