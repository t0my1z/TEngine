#pragma once

#include "TEngine/Core/Layer.h"
#include "TEngine/Events/ApplicationEvent.h"
#include "TEngine/Events/KeyEvent.h"
#include "TEngine/Events/MouseEvent.h"

namespace TEngine
{
	class TENGINE_API ImGuiLayer : public Layer
	{
	public: 

		ImGuiLayer();
		virtual ~ImGuiLayer();

		virtual void OnAttach() override; 
		virtual void OnDetach() override; 
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.f;

	};

}

