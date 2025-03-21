#pragma once

#ifdef TE_PLATFORM_WINDOWS

extern TEngine::Application* TEngine::CreateApplication(); 

int main(int argc, char** argv)
{
	auto app = TEngine::CreateApplication(); 
	app->Run();
	delete app; 
}

#endif
