#include "tepch.h"
#include "WindowsWindow.h"

#include "TEngine/Events/ApplicationEvent.h"
#include "TEngine/Events/KeyEvent.h"
#include "TEngine/Events/MouseEvent.h" 

#include "glad/glad.h"

namespace TEngine
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int _error, const char* _descp)
	{
		TE_CORE_ERROR("GLFW Error ({0}): {1}", _error, _descp);
	}


	Window* Window::Create(const WindowProps& _props)
	{
		return new WindowsWindow(_props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& _props)
	{
		Init(_props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& _props)
	{
		m_Data.m_Title = _props.m_Title;
		m_Data.m_Height = _props.m_Height;
		m_Data.m_Width = _props.m_Width;

		TE_CORE_INFO("Creating Window {0} ({1}, {2})", _props.m_Title, _props.m_Width, _props.m_Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();

			TE_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)_props.m_Width, (int)_props.m_Height, m_Data.m_Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		// Glad setup
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); 
		TE_CORE_ASSERT(status, "Could not intialize Glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				data.m_Width = width;
				data.m_Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				default:
					break;
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				default:
					break;
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void WindowsWindow::SetVSync(bool _enabled) 
	{
		if (_enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.m_VSync = _enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.m_VSync;
	}
}
