#include "tepch.h"
#include "Buffer.h" 

#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"

namespace TEngine
{
	Ref<VertexBuffer> VertexBuffer::Create(float* _vertices, uint32_t _size)
	{
		switch (Renderer::GetAPI()) 
		{
		case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexBuffer>(_vertices, _size);  
			case RendererAPI::API::None: 
				TE_CORE_ASSERT(false, "RendererAPI::None is not supported, please choose an API to render");
				return nullptr;
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* _indices, uint32_t _count)
	{
		switch (Renderer::GetAPI()) 
		{
		case RendererAPI::API::OpenGL: 
			return std::make_shared<OpenGLIndexBuffer>(_indices, _count);
		case RendererAPI::API::None: 
			TE_CORE_ASSERT(false, "RendererAPI::None is not supported, please choose an API to render"); 
			return nullptr;
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!"); 
		return nullptr;
	}
}