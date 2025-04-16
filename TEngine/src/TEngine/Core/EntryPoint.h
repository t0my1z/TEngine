#pragma once

#ifdef TE_PLATFORM_WINDOWS

extern TEngine::Application* TEngine::CreateApplication(); 

int main(int argc, char** argv)
{
	TEngine::Log::Init();
	TE_CORE_WARN("Initialized Log!");
	int a = 5;
	TE_INFO("Hello! Var={0}", a);

	auto app = TEngine::CreateApplication(); 
	app->Run();
	delete app; 
}

#endif
