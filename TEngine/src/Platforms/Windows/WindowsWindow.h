#pragma once

#include "TEngine/Core/Window.h"
#include "TEngine/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace TEngine
{

	class WindowsWindow : public Window
	{
	public:

		WindowsWindow(const WindowProps& _props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.m_Width; }
		inline unsigned int GetHeight() const override { return m_Data.m_Height; }

		virtual void SetEventCallback(const EventCallbackFn& _callback) override { m_Data.EventCallback = _callback; }
		virtual void SetVSync(bool _enabled) override;
		virtual bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_Window; }

	private:

		virtual void Init(const WindowProps& _props);
		virtual void Shutdown();

	private:

		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string m_Title;
			unsigned int m_Width;
			unsigned int m_Height;
			bool m_VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}

