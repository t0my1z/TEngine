#include <TEngine.h>

class Sandbox : public TEngine::Application
{
public:

	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};
 
TEngine::Application* TEngine::CreateApplication()
{
	return new Sandbox(); 
}
