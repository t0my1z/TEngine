#pragma once

#include <memory>

#include "TEngine/Renderer/Buffer.h"

namespace TEngine
{
	class VertexArray 
	{
	public:

		virtual ~VertexArray() {}
		 
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& _vertexBuffer ) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& _indexBuffer ) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};
}