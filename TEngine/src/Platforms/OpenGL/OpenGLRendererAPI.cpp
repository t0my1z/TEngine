#include "tepch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace TEngine 
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

		glEnable(GL_DEPTH_TEST); 
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height); 
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4 _color)
	{
		glClearColor(_color.r, _color.g, _color.b, _color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& _vertexArray)
	{
		glDrawElements(GL_TRIANGLES, _vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr); 
	}
}