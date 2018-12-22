#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>

#include <GL/glew.h>

#include "macros.h"

Shader::Shader(const unsigned int rendererId)
	: m_rendererID(rendererId) {}

Shader::~Shader() {
	GL_CALL(glDeleteProgram(m_rendererID));
}

void Shader::bind() const {
	GL_CALL(glUseProgram(m_rendererID));
}

void Shader::unbind() const {
	GL_CALL(glUseProgram(0));
}

void Shader::setUniform1i(const std::string& name, const int value) {
	GL_CALL(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1f(const std::string& name, const float v0) {
	GL_CALL(glUniform1f(getUniformLocation(name), v0));
}

void Shader::setUniform2f(const std::string& name, const float v0, const float v1) {
	GL_CALL(glUniform2f(getUniformLocation(name), v0, v1));
}

void Shader::setUniform3f(const std::string& name, const float v0, const float v1, const float v2) {
	GL_CALL(glUniform3f(getUniformLocation(name), v0, v1, v2));
}

void Shader::setUniform4f(const std::string& name, const float v0, const float v1, const float v2, const float v3) {
	GL_CALL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformVec2(const std::string& name, const glm::vec2& v) {
	GL_CALL(glUniform2fv(getUniformLocation(name), 1, &v[0]));
}

void Shader::setUniformVec3(const std::string& name, const glm::vec3& v) {
	GL_CALL(glUniform3fv(getUniformLocation(name), 1, &v[0]));
}

void Shader::setUniformVec4(const std::string& name, const glm::vec4& v) {
	GL_CALL(glUniform4fv(getUniformLocation(name), 1, &v[0]));
}

void Shader::setUniformMat3(const std::string& name, const glm::mat3& m) {
	GL_CALL(glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]));
}

void Shader::setUniformMat4(const std::string& name, const glm::mat4& m) {
	GL_CALL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]));
}

void Shader::setUniformBool(const std::string& name, const bool value) {
	GL_CALL(glUniform1i(getUniformLocation(name), value));
}

std::string Shader::parseFile(const ShaderType type, const std::string& filePath) {
	std::ifstream stream(filePath, std::ios::in);
	std::string line;
	std::stringstream sourceCode;

	if (!stream.is_open()) {
		DEBUG(std::cout << "Can not open shader file!" << std::endl);
		return "";
	}

	// check if file is empty
	if (!getline(stream, line)) {
		DEBUG(std::cout << "Shader file is empty!" << std::endl);
		return "";
	}

	// replace BOM
	line = line.replace(0, 3, "");
	if (line.empty() && !getline(stream, line)) {
		DEBUG(std::cout << "Shader file is empty!" << std::endl);
		return "";
	}

	// read first line (shader type) and check
	std::smatch shaderTypeMatch;
	if (!std::regex_search(line, shaderTypeMatch, std::regex("(?:#shader )(\\w+)"))) {
		DEBUG(std::cout << "Can not find shader type: " << line << std::endl);
		return "";
	}

	const std::string shaderType = shaderTypeMatch[1];
	std::string expected;

	switch (type) {
	case VERTEX:
		expected = "vertex";
		break;
	case GEOMETRY:
		expected = "geometry";
		break;
	case FRAGMENT:
		expected = "fragment";
		break;
	}

	if (shaderType != expected) {
		DEBUG(std::cout << "Unexpected shader type '" << shaderType << "'. Expected '" << expected << "'" << std::endl);
		return "";
	}

	DEBUG(std::cout << "Parsing " << shaderType << " shader from '" << filePath << "'" << std::endl);

	DEBUG(std::cout << "--------- Start of shader code ---------" << std::endl);

	while (getline(stream, line)) {
		DEBUG(std::cout << line << std::endl);
		sourceCode << line << "\n";
	}
	DEBUG(std::cout << "--------- End of shader code ---------" << std::endl);
	return sourceCode.str();
}

unsigned int Shader::compileShaderSource(const ShaderType type, const std::string& source) {
	unsigned int glType;
	DEBUG(const char* typeName);
	switch (type) {
	case VERTEX:
		glType = GL_VERTEX_SHADER;
		DEBUG(typeName = "vertex");
		break;
	case GEOMETRY:
		glType = GL_GEOMETRY_SHADER;
		DEBUG(typeName = "geometry");
		break;
	case FRAGMENT:
		glType = GL_FRAGMENT_SHADER;
		DEBUG(typeName = "fragment");
		break;
	default:
		return -1;
	}

	DEBUG(std::cout << "Compiling " << typeName << " shader" << std::endl);
	GL_CALL(const unsigned int id = glCreateShader(glType));
	const char* src = source.c_str();
	GL_CALL(glShaderSource(id, 1, &src, nullptr));
	GL_CALL(glCompileShader(id));

	int result;
	GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	DEBUG(
		if (result == GL_FALSE) {
			int len;
			GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len));
			auto* message = (char*) alloca(len * sizeof(char));
			GL_CALL(glGetShaderInfoLog(id, len, &len, message));
			std::cout << "Failed to compile " << typeName << "shader!" << std::endl;
			std::cout << message << std::endl;
			GL_CALL(glDeleteShader(id));
			return 0;
		}
	)

	return id;
}

bool checkLinking(unsigned int program) {

	GLint isLinked;
	GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &isLinked));
	DEBUG(
		if (isLinked == GL_FALSE) {
			GLint maxLength;
			GL_CALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength));

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength + 1);
			GL_CALL(glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]));
			std::cout << "Failed to link program" << std::endl << "Log:" << std::endl << std::string(infoLog.begin(), infoLog.end() - 1) << std::endl;

			// delete[] log;
			return false;
		}
	)
	return true;
}

unsigned int Shader::createProgram(const unsigned int vertexId, const unsigned int fragmentId) {
	GL_CALL(const unsigned int program = glCreateProgram());

	GL_CALL(glAttachShader(program, vertexId));
	GL_CALL(glAttachShader(program, fragmentId));
	GL_CALL(glLinkProgram(program));
	if (!checkLinking(program)) {
		// The program is useless now. So delete it.
		glDeleteProgram(program);
		return -1;
	}
	GL_CALL(glValidateProgram(program));
	return program;
}

unsigned int Shader::createProgram(const unsigned int vertexId, const unsigned int geometryId, const unsigned int fragmentId) {
	GL_CALL(const unsigned int program = glCreateProgram());

	GL_CALL(glAttachShader(program, vertexId));
	GL_CALL(glAttachShader(program, geometryId));
	GL_CALL(glAttachShader(program, fragmentId));
	GL_CALL(glLinkProgram(program));
	if (!checkLinking(program)) {
		// The program is useless now. So delete it.
		glDeleteProgram(program);
		return -1;
	}
	GL_CALL(glValidateProgram(program));

	return program;
}

int Shader::getUniformLocation(const std::string& name) {
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		return m_uniformLocationCache[name];

	GL_CALL(const int location = glGetUniformLocation(m_rendererID, name.c_str()));
	if (location == -1) {
		DEBUG(printf("Waring uniform '%s' doesn't exist!\n", name.c_str()));
	}

	m_uniformLocationCache[name] = location;
	return location;
}

unsigned Shader::compileFile(const ShaderType type, const std::string& path) {
	return compileShaderSource(type, parseFile(type, path));
}

Shader* Shader::fromSource(const std::string& vertexSource, const std::string& fragmentSource) {
	const unsigned int vertexId = compileShaderSource(VERTEX, vertexSource);
	const unsigned int fragmentId = compileShaderSource(FRAGMENT, fragmentSource);
	auto* out = fromCompiledSource(vertexId, fragmentId);
	GL_CALL(glDeleteShader(vertexId));
	GL_CALL(glDeleteShader(fragmentId));
	return out;
}

Shader* Shader::fromSource(const std::string& vertexSource, const std::string& geometrySource, const std::string& fragmentSource) {
	const unsigned int vertexId = compileShaderSource(VERTEX, vertexSource);
	const unsigned int geometryId = compileShaderSource(GEOMETRY, geometrySource);
	const unsigned int fragmentId = compileShaderSource(FRAGMENT, fragmentSource);
	auto* out = fromCompiledSource(vertexId, geometryId, fragmentId);
	GL_CALL(glDeleteShader(vertexId));
	GL_CALL(glDeleteShader(geometryId));
	GL_CALL(glDeleteShader(fragmentId));
	return out;
}

Shader* Shader::fromCompiledSource(const unsigned int vertexId, const unsigned int fragmentId) {
	return new Shader(createProgram(vertexId, fragmentId));
}

Shader* Shader::fromCompiledSource(const unsigned int vertexId, const unsigned int geometryId, const unsigned int fragmentId) {
	return new Shader(createProgram(vertexId, geometryId, fragmentId));
}

Shader* Shader::fromFiles(const std::string& vertexPath, const std::string& fragmentPath) {
	return fromCompiledSource(compileFile(VERTEX, vertexPath), compileFile(FRAGMENT, fragmentPath));
}

Shader* Shader::fromFiles(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath) {
	return fromSource(parseFile(VERTEX, vertexPath), parseFile(GEOMETRY, geometryPath), parseFile(FRAGMENT, fragmentPath));
}
