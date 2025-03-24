#include <TEngine.h>

class Sandbox : public TEngine::Application
{
public:

	Sandbox()
	{
		PushOverlay(new TEngine::ImGuiLayer()); 
	}

	~Sandbox()
	{

	}
};
 
TEngine::Application* TEngine::CreateApplication()
{
	return new Sandbox(); 
}
