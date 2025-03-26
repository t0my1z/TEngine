#include "tepch.h"
#include "RenderCommand.h"
#include "Platforms/OpenGL/OpenGLRendererAPI.h" 

namespace TEngine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI(); 
}