#pragma once

#include <string>

namespace TEngine
{
	class Shader
	{
	public:

		virtual ~Shader() {} 

		virtual void Bind() const = 0; 
		virtual void Unbind() const = 0; 

		static Shader* Create(const std::string& _vertexSrc, const std::string& _fragmentSrc); 
	};
}
