#include "tepch.h"
#include "VertexArray.h"

#include "Renderer.h" 
#include "Platforms/OpenGL/OpenGLVertexArray.h"

namespace TEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) 
		{
		case RendererAPI::API::OpenGL: 
			return new OpenGLVertexArray();  
		case RendererAPI::API::None: 
			TE_CORE_ASSERT(false, "RendererAPI::None is not supported, please choose an API to render");
			return nullptr;
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}