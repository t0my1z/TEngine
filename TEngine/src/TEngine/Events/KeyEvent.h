#pragma once

#include "Event.h"

namespace TEngine 
{
	
	class TENGINE_API KeyEvent : public Event
	{
	public:

		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:

		KeyEvent(int _keycode)
			: m_KeyCode(_keycode) {}

		int m_KeyCode; 
	};


	class TENGINE_API KeyPressedEvent : public KeyEvent
	{
	public:
	
		KeyPressedEvent(int _keycode, int _repeatCount)
			: KeyEvent(_keycode), m_RepeatCount(_repeatCount) {}
	
		
		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		} 

		EVENT_CLASS_TYPE(KeyPressed) 

	private: 
	
		int m_RepeatCount; 
	
	};

	class TENGINE_API KeyReleasedEvent : public KeyEvent 
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased) 
	};
}