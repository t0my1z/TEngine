#include "tepch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace TEngine
{
	////////////////////////////////////////////////////////////
	///// VERTEX BUFFER ////////////////////////////////////////
	////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* _vertices, uint32_t _size)
	{
		TE_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);  
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);  
		glBufferData(GL_ARRAY_BUFFER, _size, _vertices, GL_STATIC_DRAW); 
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		TE_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);  
	}

	void OpenGLVertexBuffer::Bind() const
	{
		TE_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);  
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		TE_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0); 
	}

	////////////////////////////////////////////////////////////
	///// INDEX BUFFER /////////////////////////////////////////
	////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* _indices, uint32_t _count) 
		: m_Count(_count) 
	{ 
		TE_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID); 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), _indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		TE_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID); 
	}

	void OpenGLIndexBuffer::Bind() const
	{
		TE_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); 
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		TE_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::GetCount() const
	{
		return m_Count; 
	}
}