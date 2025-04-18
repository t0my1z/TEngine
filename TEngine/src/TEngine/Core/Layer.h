#pragma once
#include "TEngine/Core/Core.h"
#include "TEngine/Events/Event.h"
#include "TEngine/Core/Timestep.h"

namespace TEngine
{
	class TENGINE_API Layer
	{
	public:

		Layer(const std::string& _name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {} 
		virtual void OnEvent(Event& _event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:

		std::string m_DebugName;
	};
}

