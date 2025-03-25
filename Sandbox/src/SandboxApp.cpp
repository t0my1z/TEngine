#include <TEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public TEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (TEngine::Input::IsKeyPressed(TE_KEY_TAB)) 
			TE_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(TEngine::Event& event) override 
	{
		if (event.GetEventType() == TEngine::EventType::KeyPressed)
		{
			TEngine::KeyPressedEvent& e = (TEngine::KeyPressedEvent&)event;  
			if (e.GetKeyCode() == TE_KEY_TAB) 
				TE_TRACE("Tab key is pressed (event)!"); 
			TE_TRACE("{0}", (char)e.GetKeyCode()); 
		}
	}

};

class Sandbox : public TEngine::Application
{
public:

	Sandbox()
	{
		PushLayer(new ExampleLayer());  
	}

	~Sandbox()
	{

	}
};
 
TEngine::Application* TEngine::CreateApplication()
{
	return new Sandbox(); 
}
