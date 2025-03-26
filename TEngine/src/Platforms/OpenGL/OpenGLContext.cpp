#include "tepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"

namespace TEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* _windowHandle)
		: m_windowHandle(_windowHandle)
	{
		TE_CORE_ASSERT(m_windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle); 
		// Glad setup
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TE_CORE_ASSERT(status, "Could not intialize Glad!");

		TE_CORE_INFO("OpenGL Info:");  
		TE_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		TE_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		TE_CORE_INFO("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle); 
	}
}