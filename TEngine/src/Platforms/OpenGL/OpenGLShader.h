#pragma once

#include "Renderer/Shader.h"

namespace TEngine
{

	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const std::string& _vertexSrc, const std::string& _fragmentSrc); 
		virtual ~OpenGLShader(); 

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:

		uint32_t m_RendererID;

	};

}