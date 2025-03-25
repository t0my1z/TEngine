#pragma once
#include "Renderer/GraphicsContext.h"

struct GLFWwindow; 

namespace TEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:

		OpenGLContext(GLFWwindow* _windowHandle); 

		virtual void Init() override;
		virtual void SwapBuffers() override; 

	private:

		GLFWwindow* m_windowHandle;

	};
}