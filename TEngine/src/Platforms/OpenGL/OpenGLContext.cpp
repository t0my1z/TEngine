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

		#ifdef TE_ENABLE_ASSERTS 

		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor); 
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		TE_CORE_ASSERT((versionMajor >= 4 || (versionMajor >= 4 && versionMinor >= 5)),
			"TEngine requires at least OpenGL version 4.5");

		#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle); 
	}
}