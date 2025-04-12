#include "tepch.h"
#include "Shader.h"

#include "Renderer.h" 
#include "Platforms/OpenGL/OpenGLShader.h"

namespace TEngine
{

	Shader* Shader::Create(const std::string& _vertexSrc, const std::string& _fragmentSrc)
	{
		switch (Renderer::GetAPI()) 
		{
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(_vertexSrc, _fragmentSrc); 
		case RendererAPI::API::None: 
			TE_CORE_ASSERT(false, "RendererAPI::None is not supported, please choose an API to render");
			return nullptr;
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}