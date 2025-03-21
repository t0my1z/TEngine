#pragma once

//When we build the dll from TEngine, the macro will export, and when we use it in another project, it'll import

#ifdef TE_PLATFORM_WINDOWS 
	#ifdef TE_BUILD_DLL
		#define TENGINE_API __declspec(dllexport) 
	#else
		#define TENGINE_API __declspec(dllimport) 
	#endif
#else
	#error TEngine only supports windows
#endif