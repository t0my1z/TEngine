#pragma once

#include "TEngine/Core.h"

namespace TEngine
{
	class TENGINE_API GraphicsContext
	{
	public:

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}