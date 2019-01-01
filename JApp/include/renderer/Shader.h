#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace JApp { namespace Renderer {

	class Shader {
	private:
		std::unordered_map<std::string, int> m_uniformLocationCache;
		explicit Shader(unsigned int rendererId);
	public:
		unsigned int m_rendererID;

		enum ShaderType {
			VERTEX,
			GEOMETRY,
			FRAGMENT
		};

		~Shader();

		void bind() const;
		void unbind() const;

		/* set uniforms */
		void setUniform1i(const std::string& name, int value);
		void setUniform1f(const std::string& name, float v0);
		void setUniform2f(const std::string& name, float v0, float v1);
		void setUniform3f(const std::string& name, float v0, float v1, float v2);
		void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void setUniformVec2(const std::string& name, const glm::vec2& v);
		void setUniformVec3(const std::string& name, const glm::vec3& v);
		void setUniformVec4(const std::string& name, const glm::vec4& v);
		void setUniformMat3(const std::string& name, const glm::mat3& m);
		void setUniformMat4(const std::string& name, const glm::mat4& m);
		void setUniformBool(const std::string& name, bool value);
		void setUniformArrF(const std::string& name, float* arr, unsigned int size);
		void setUniformArrI(const std::string& name, int* arr, unsigned int size);

		static unsigned int compileFile(const ShaderType type, const std::string& path);

		static Shader* fromSource(const std::string& vertexSource, const std::string& fragmentSource);
		static Shader* fromSource(const std::string& vertexSource, const std::string& geometrySource,
		                          const std::string& fragmentSource);

		static Shader* fromCompiledSource(unsigned int vertexId, unsigned int fragmentId);
		static Shader* fromCompiledSource(unsigned int vertexId, unsigned int geometryId, unsigned int fragmentId);

		static Shader* fromFiles(const std::string& vertexPath, const std::string& fragmentPath);
		static Shader* fromFiles(const std::string& vertexPath, const std::string& geometryPath,
		                         const std::string& fragmentPath);

	private:
		static std::string parseFile(ShaderType type, const std::string& filePath);
		static unsigned int compileShaderSource(ShaderType type, const std::string& source);
		static unsigned int createProgram(unsigned int vertexId, unsigned int fragmentId);
		static unsigned int createProgram(unsigned int vertexId, unsigned int geometryId, unsigned int fragmentId);

		int getUniformLocation(const std::string& name);

	};

}}
