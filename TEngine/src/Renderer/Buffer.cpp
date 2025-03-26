#include "tepch.h"
#include "Buffer.h" 

#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"

namespace TEngine
{
	VertexBuffer* VertexBuffer::Create(float* _vertices, uint32_t _size)
	{
		switch (Renderer::GetAPI()) 
		{
			case RendererAPI::OpenGL:
				return new OpenGLVertexBuffer(_vertices, _size); 
			case RendererAPI::None: 
				TE_CORE_ASSERT(false, "RendererAPI::None is not supported, please choose an API to render");
				return nullptr;
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* _indices, uint32_t _count)
	{
		switch (Renderer::GetAPI()) 
		{
		case RendererAPI::OpenGL: 
			return new OpenGLIndexBuffer(_indices, _count); 
		case RendererAPI::None: 
			TE_CORE_ASSERT(false, "RendererAPI::None is not supported, please choose an API to render"); 
			return nullptr;
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!"); 
		return nullptr;
	}
}