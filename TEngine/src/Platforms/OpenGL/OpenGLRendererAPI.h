#pragma once

#include "Renderer/RendererAPI.h"

namespace TEngine
{

	class OpenGLRendererAPI : public RendererAPI
	{
	public:

		virtual void SetClearColor(const glm::vec4 _color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& _vertexArray) override; 
	};
}