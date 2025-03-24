#pragma once

#include "TEngine/Layer.h"
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

		virtual void OnAttach(); 
		virtual void OnDetach(); 
		virtual void OnUpdate(); 
		virtual void OnEvent(Event& _event);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& _event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& _event);
		bool OnMouseMovedEvent(MouseMovedEvent& _event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& _event);
		bool OnKeyPressedEvent(KeyPressedEvent& _event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& _event);
		bool OnKeyTypedEvent(KeyTypedEvent& _event);
		bool OnWindowResizeEvent(WindowResizeEvent& _event);

	private:
		float m_Time = 0.f;

	};

}

