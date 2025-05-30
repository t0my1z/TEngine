#include "tepch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace TEngine
{
	static GLenum ShaderTypeFromString(std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER; 
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

		TE_CORE_ASSERT(false, "Unknow shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& _vertexSrc, const std::string& _fragmentSrc)
		: m_RendererID(0), m_Name(name) 
	{
		TE_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources; 
		sources[GL_VERTEX_SHADER] = _vertexSrc; 
		sources[GL_FRAGMENT_SHADER] = _fragmentSrc;  
		Compile(sources); 
	}

	OpenGLShader::OpenGLShader(const std::string& path) 
		: m_RendererID(0)
	{
		TE_PROFILE_FUNCTION();

		std::string shaderSource = ReadFile(path); 
		auto shaderSources = PreProcess(shaderSource);
		Compile(shaderSources); 

		// Extract name from filepath
		auto lastSlash = path.find_last_of("/\\"); 
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		m_Name = path.substr(lastSlash, count); 
	}

	OpenGLShader::~OpenGLShader()
	{
		TE_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& file)
	{
		TE_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(file, std::ios::in | std::ios::binary); 
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			TE_CORE_ERROR("Could not open file '{0}'", file);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		TE_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			TE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			TE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		TE_PROFILE_FUNCTION(); 

		GLuint program = glCreateProgram();
		TE_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");

		std::array<GLenum, 2> glShaderIds;
		int glShaderIdIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);
			const GLchar* sourceCStr = (const GLchar*)source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				TE_CORE_ERROR("{0}", infoLog.data());
				TE_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIds[glShaderIdIndex++] = shader;
		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0; 
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			// Don't leak shaders either.
			for (GLenum shader : glShaderIds)
			{
				glDeleteShader(shader);
			}

			TE_CORE_ERROR("{0}", infoLog.data());
			TE_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		for (GLenum shader : glShaderIds)
		{
			glDetachShader(program, shader);
		}

		m_RendererID = program;
	}

	void OpenGLShader::Bind() const
	{
		TE_PROFILE_FUNCTION(); 

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		TE_PROFILE_FUNCTION(); 

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		TE_PROFILE_FUNCTION(); 

		UploadUniformInt(name, value); 
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)  
	{
		TE_PROFILE_FUNCTION(); 

		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value) 
	{
		TE_PROFILE_FUNCTION(); 

		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value) 
	{
		TE_PROFILE_FUNCTION(); 

		UploadUniformMat4(name, value); 
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, const int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value); 
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, const float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str()); 
		glUniform1f(location, value); 
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str()); 
		glUniform2f(location, values.x, values.y); 
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str()); 
		glUniform3f(location, values.x, values.y, values.z); 
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w); 
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str()); 
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); 
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); 
	}
}