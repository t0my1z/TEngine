#pragma once
#include "Core.h"

namespace TEngine
{
	class TENGINE_API Application
	{
		public:

		Application();
		virtual ~Application(); 

		void Run();

	};

	//To be defined in client
	Application* CreateApplication();
}

