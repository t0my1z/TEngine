#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "TEngine/Log.h"

namespace TEngine
{

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent ev(1280, 720);
		TE_TRACE(ev);

		while (true)
		{

		}
	}
}