#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace TEngine
{

	class TENGINE_API Log
	{
		
	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger; 
		static std::shared_ptr<spdlog::logger> s_ClientLogger;  

	};

}


//Core Log Macros
#define TE_CORE_TRACE(...)   ::TEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)  
#define TE_CORE_INFO(...)    ::TEngine::Log::GetCoreLogger()->info(__VA_ARGS__) 
#define TE_CORE_WARN(...)    ::TEngine::Log::GetCoreLogger()->warn(__VA_ARGS__) 
#define TE_CORE_FATAL(...)   ::TEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)    

//Cient Log Macros 
#define TE_TRACE(...)   ::TEngine::Log::GetClientLogger()->trace(__VA_ARGS__)  
#define TE_INFO(...)    ::TEngine::Log::GetClientLogger()->info(__VA_ARGS__) 
#define TE_WARN(...)    ::TEngine::Log::GetClientLogger()->warn(__VA_ARGS__)  
#define TE_FATAL(...)   ::TEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)   

