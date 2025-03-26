#include "tepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace TEngine
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType _type)
	{
		switch (_type)
		{
		case TEngine::ShaderDataType::None:		break;
		case TEngine::ShaderDataType::Float:	return GL_FLOAT;
		case TEngine::ShaderDataType::Float2:	return GL_FLOAT;
		case TEngine::ShaderDataType::Float3:	return GL_FLOAT;
		case TEngine::ShaderDataType::Float4:	return GL_FLOAT;
		case TEngine::ShaderDataType::Mat3:		return GL_FLOAT;
		case TEngine::ShaderDataType::Mat4:		return GL_FLOAT;
		case TEngine::ShaderDataType::Int:		return GL_INT;
		case TEngine::ShaderDataType::Int2:		return GL_INT;
		case TEngine::ShaderDataType::Int3:		return GL_INT;
		case TEngine::ShaderDataType::Int4:		return GL_INT;
		case TEngine::ShaderDataType::Bool:		return GL_BOOL;
		}

		TE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID); 
	}

	OpenGLVertexArray::~OpenGLVertexArray() 
	{
		glDeleteVertexArrays(1, &m_RendererID);   
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID); 
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0); 
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& _vertexBuffer)
	{
		TE_CORE_ASSERT(_vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID); 
		_vertexBuffer->Bind();

		uint32_t index = 0; 
		for (const auto& element : _vertexBuffer->GetLayout()) 
		{
			glEnableVertexAttribArray(index); 
			glVertexAttribPointer( 
				index, element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, 
				_vertexBuffer->GetLayout().GetStride(),  
				(const void*)element.Offset 
			); 
			++index; 
		}

		m_VertexBuffers.push_back(_vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& _indexBuffer)
	{
		glBindVertexArray(m_RendererID); 
		_indexBuffer->Bind();

		m_IndexBuffer = _indexBuffer;
	}

}