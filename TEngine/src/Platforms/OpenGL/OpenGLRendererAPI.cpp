#include "tepch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace TEngine 
{
	void OpenGLRendererAPI::SetClearColor(const glm::vec4 _color)
	{
		glClearColor(_color.r, _color.g, _color.b, _color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& _vertexArray)
	{
		glDrawElements(GL_TRIANGLES, _vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr); 
	}
}