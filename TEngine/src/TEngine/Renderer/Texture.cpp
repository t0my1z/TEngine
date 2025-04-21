#include "tepch.h"
#include "Texture.h"
#include "Renderer.h"

#include "Platforms/OpenGL/OpenGLTexture.h"

namespace TEngine
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI()) 
		{
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height); 
			case RendererAPI::API::None: TE_CORE_ASSERT(false, "RendererAPI::None is not supported, please choose an API to render"); return nullptr;
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI()) 
		{
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
			case RendererAPI::API::None:   TE_CORE_ASSERT(false, "RendererAPI::None is not supported, please choose an API to render"); return nullptr;
		}

		TE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}