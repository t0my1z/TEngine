#pragma once

#include <string>
#include <glm/glm.hpp>

namespace TEngine
{
	class Shader
	{
	public:

		virtual ~Shader() = default;

		virtual void Bind() const = 0; 
		virtual void Unbind() const = 0; 

		virtual void SetInt(const std::string& name, const int value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& _vertexSrc, const std::string& _fragmentSrc);
		static Ref<Shader> Create(const std::string& _path);  
	};

	class ShaderLibrary
	{
	public:

		void Add(const std::string& name, const Ref<Shader>& shader); 
		void Add(const Ref<Shader>& shader);

		Ref<Shader> Load(const std::string& filePath); //assets/shaders/...
		Ref<Shader> Load(const std::string& name, const std::string& filePath); 
  
		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}
