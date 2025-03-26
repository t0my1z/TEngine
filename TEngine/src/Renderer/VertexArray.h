#pragma once

#include <memory>

#include "Renderer/Buffer.h"

namespace TEngine
{
	class VertexArray 
	{
	public:

		virtual ~VertexArray() {}
		 
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& _vertexBuffer ) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& _indexBuffer ) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0; 

		static VertexArray* Create();
	};
}