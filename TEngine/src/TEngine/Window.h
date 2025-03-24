#pragma once
#include "tepch.h"

#include "Core.h"
#include "Events/Event.h"

namespace TEngine
{
	struct WindowProps
	{
		WindowProps(const std::string& _title = "TEngine",
			unsigned int _width = 1280,
			unsigned int _height = 720)
			: m_Title(_title), m_Width(_width), m_Height(_height)
		{

		}

		std::string m_Title;
		unsigned int m_Width;
		unsigned int m_Height;
	};

	// Interace of desktop system Window. To be implemented for each OS we want to support
	class TENGINE_API Window
	{

	public:

		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& _callback) = 0; 
		virtual void SetVSync(bool _enabled) = 0;
		virtual bool IsVSync() const = 0;

		//Gets implemented per platform, in their respective cpp
		static Window* Create(const WindowProps& props = WindowProps());
	};


}