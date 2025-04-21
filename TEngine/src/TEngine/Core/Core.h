#pragma once

#include <memory>

//When we build the dll from TEngine, the macro will export, and when we use it in another project, it'll import
//Irrelevant, since we now build as a static library, instead of a dynamic one.
#ifdef TE_PLATFORM_WINDOWS 
	#if TE_DYNAMIC_LINK
		#ifdef TE_BUILD_DLL
			#define TENGINE_API __declspec(dllexport) 
		#else
			#define TENGINE_API __declspec(dllimport) 
		#endif
	#else
		#define TENGINE_API
#endif
#else
	#error TEngine only supports windows
#endif 

#ifdef TE_DEBUG
	#define TE_ENABLE_ASSERTS
#endif

#ifdef TE_ENABLE_ASSERTS
#define TE_ASSERT(x, ...) { if(!(x)) { TE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }  
#define TE_CORE_ASSERT(x, ...) { if(!(x)) { TE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }  
#else
#define TE_ASSERT(x, ...) 
#define TE_CORE_ASSERT(x, ...) 
#endif

#define BIT(x) (1 << x)

#define TE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace TEngine 
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) 
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;  
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}