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