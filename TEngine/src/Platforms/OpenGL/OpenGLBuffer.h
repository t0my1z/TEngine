#pragma once
#include "Renderer/Buffer.h"

namespace TEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:

		OpenGLVertexBuffer(float* _vertices, uint32_t _size); 
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; } 
		virtual void SetLayout(const BufferLayout& _layout) override { m_Layout = _layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer 
	{
	public:

		OpenGLIndexBuffer(uint32_t* _indices, uint32_t _count); 
		virtual ~OpenGLIndexBuffer(); 

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override;

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}