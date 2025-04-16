#pragma once

#include "RendererAPI.h"

namespace TEngine
{
	class RenderCommand
	{
	public:

		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height); 
		}

		inline static void SetClearColor(const glm::vec4 _color)
		{
			s_RendererAPI->SetClearColor(_color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& _vertexArray)
		{
			s_RendererAPI->DrawIndexed(_vertexArray); 
		}

	private:
		static RendererAPI* s_RendererAPI; 
	};
}