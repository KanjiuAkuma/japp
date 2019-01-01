#include "Shader.h"

#include <fstream>
#include <sstream>
#include <regex>

#include "macros.h"
#include "logger/Log.h"

namespace JApp { namespace Renderer {

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

	void Shader::setUniformArrF(const std::string& name, float* arr, const unsigned int size) {
		GL_CALL(glUniform1fv(getUniformLocation(name), size, arr));
	}


	void Shader::setUniformArrI(const std::string& name, int* arr, const unsigned int size) {
		GL_CALL(glUniform1iv(getUniformLocation(name), size, arr));
	}

	std::string Shader::parseFile(const ShaderType type, const std::string& filePath) {
		std::ifstream stream(filePath, std::ios::in);
		std::string line;
		std::stringstream sourceCode;

		if (!stream.is_open()) {
			APP_CORE_ERROR("Can not open shader file! '{}'", filePath);
			return "";
		}

		// check if file is empty
		if (!getline(stream, line)) {
			APP_CORE_ERROR("Shader file is empty! '{}'", filePath);
			return "";
		}

		// read first line (shader type) and check
		std::smatch shaderTypeMatch;
		if (!std::regex_search(line, shaderTypeMatch, std::regex("(?:#shader )(\\w+)"))) {
			APP_CORE_ERROR("Can not find shader type in line: {}", line);
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
			APP_CORE_ERROR("Unexpected shader type '{}'. Expected '{}'", shaderType, expected);
			return "";
		}

		APP_CORE_TRACE("Parsing {} shader from '{}'", shaderType, filePath);

		while (getline(stream, line)) {
			APP_CORE_TRACE(line);
			sourceCode << line << "\n";
		}
		APP_CORE_TRACE("--------- End of shader code ---------");
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

		APP_CORE_TRACE("Compiling {} shader", typeName);
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
				auto* message = (char*)alloca(len * sizeof(char));
				GL_CALL(glGetShaderInfoLog(id, len, &len, message));
				APP_CORE_ERROR("Failed to compile {} shader", typeName);
				APP_CORE_ERROR(message);
				GL_CALL(glDeleteShader(id));
				return 0;
			}
		)

		return id;
	}

	bool checkLinking(const unsigned int program) {

		GLint isLinked;
		GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &isLinked));
		DEBUG(
			if (isLinked == GL_FALSE) {
				GLint maxLength;
				GL_CALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength));

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength + 1);
				GL_CALL(glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]));
				APP_CORE_ERROR("Failed to link program");
				APP_CORE_ERROR("Log:{}", std::string(infoLog.begin(), infoLog.end() - 1));

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

	unsigned int Shader::createProgram(const unsigned int vertexId, const unsigned int geometryId,
	                                   const unsigned int fragmentId) {
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
			APP_WARN("Waring uniform '{}' doesn't exist!", name.c_str());
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

	Shader* Shader::fromSource(const std::string& vertexSource, const std::string& geometrySource,
	                           const std::string& fragmentSource) {
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

	Shader* Shader::fromCompiledSource(const unsigned int vertexId, const unsigned int geometryId,
	                                   const unsigned int fragmentId) {
		return new Shader(createProgram(vertexId, geometryId, fragmentId));
	}

	Shader* Shader::fromFiles(const std::string& vertexPath, const std::string& fragmentPath) {
		return fromCompiledSource(compileFile(VERTEX, vertexPath), compileFile(FRAGMENT, fragmentPath));
	}

	Shader* Shader::fromFiles(const std::string& vertexPath, const std::string& geometryPath,
	                          const std::string& fragmentPath) {
		return fromSource(parseFile(VERTEX, vertexPath), parseFile(GEOMETRY, geometryPath),
		                  parseFile(FRAGMENT, fragmentPath));
	}

}}
