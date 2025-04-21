#pragma once

#ifdef TE_PLATFORM_WINDOWS

extern TEngine::Application* TEngine::CreateApplication(); 

int main(int argc, char** argv)
{
	TEngine::Log::Init();

	TE_PROFILE_BEGIN_SESSION("Startup", "TEngineProfile-Startup.json"); 
	auto app = TEngine::CreateApplication(); 
	TE_PROFILE_END_SESSION(); 

	TE_PROFILE_BEGIN_SESSION("Runtime", "TEngineProfile-Runtime.json");
	app->Run();
	TE_PROFILE_END_SESSION();

	TE_PROFILE_BEGIN_SESSION("Shutdown", "TEngineProfile-Shutdown.json");
	delete app; 
	TE_PROFILE_END_SESSION();  
}

#endif
