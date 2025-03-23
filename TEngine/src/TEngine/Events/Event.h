#pragma once

#include "TEngine/Core.h"

#include <string>
#include <functional>

namespace TEngine
{

	// Events are currently blocking, when it occurs, 
	// it immediately gets dispatched and must be dealth with right then
	// For the future, doing buffer events in an event bus and procces them 
	// during the event part of the update state would be better

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
		virtual EventType GetEventType() const override { return GetStaticType(); } \
		virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class TENGINE_API Event
	{
		friend class EventDispatcher;

	public:

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0; 
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory _category)
		{
			return GetCategoryFlags() & _category;
		}

	protected:

		bool m_Handled = false;

	};


	class TENGINE_API EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:

		EventDispatcher(Event& _event)
			: m_Event(_event)
		{

		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:

		Event& m_Event;
	};

	inline std::string format_as(const Event& e) 
	{
		return e.ToString();
	}
}