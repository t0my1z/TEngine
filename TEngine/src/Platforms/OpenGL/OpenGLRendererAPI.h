#pragma once

#include "TEngine/Renderer/RendererAPI.h"

namespace TEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:

		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(const glm::vec4 _color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& _vertexArray) override;
	};
}