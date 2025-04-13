#pragma once

#include "Renderer/RendererAPI.h"

namespace TEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:

		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4 _color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& _vertexArray) override;
	};
}