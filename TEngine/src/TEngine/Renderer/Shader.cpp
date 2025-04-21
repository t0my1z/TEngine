#include "tepch.h"
#include "Shader.h"

#include "Renderer.h" 
#include "Platforms/OpenGL/OpenGLShader.h"

namespace TEngine
{
	 
	Ref<Shader> Shader::Create(const std::string& name, const std::string& _vertexSrc, const std::string& _fragmentSrc)
	{
		switch (Renderer::GetAPI()) 
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(name, _vertexSrc, _fragmentSrc);
		case RendererAPI::API::None: 
			TE_CORE_ASSERT(false, "RendererAPI::None is not supported, please choose an API to render");
			return nullptr;
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& _path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(_path);
		case RendererAPI::API::None:
			TE_CORE_ASSERT(false, "RendererAPI::None is not supported, please choose an API to render");
			return nullptr;
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		TE_CORE_ASSERT(!Exists(name), "Shader already exists"); 
		m_Shaders[name] = shader;  
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName(); 
		Add(name, shader);  
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Shader::Create(filePath); 
		Add(shader); 
		return shader;  
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		auto shader = Shader::Create(filePath); 
		Add(name, shader); 
		return shader; 
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		TE_CORE_ASSERT(Exists(name), "Shader not found");     
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();  
	}
}