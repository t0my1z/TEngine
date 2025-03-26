#pragma once

#include "RenderCommand.h"

namespace TEngine
{
	class Renderer
	{
	public:

		static void BeginScene();  
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& _vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}