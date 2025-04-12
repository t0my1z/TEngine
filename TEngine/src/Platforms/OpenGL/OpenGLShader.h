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

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

	private:

		uint32_t m_RendererID;

	};

}