#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace TEngine
{
	class RendererAPI
	{
	public:

		enum class API
		{
			None = 0,
			OpenGL = 1,
			Direct3D = 2
		};

	public:
		virtual void SetClearColor(const glm::vec4 _color) = 0; 
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& _vertexArray) = 0;

		inline static API GetAPI() { return s_API; } 

	private:

		static API s_API; 
	};

}