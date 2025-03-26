#pragma once

namespace TEngine
{
	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType _type)
	{
		switch (_type)
		{
			case TEngine::ShaderDataType::None:		break;
			case TEngine::ShaderDataType::Float:	return 4;
			case TEngine::ShaderDataType::Float2:	return 4 * 2;
			case TEngine::ShaderDataType::Float3:	return 4 * 3;
			case TEngine::ShaderDataType::Float4:	return 4 * 4;
			case TEngine::ShaderDataType::Mat3:		return 4 * 3 * 3;
			case TEngine::ShaderDataType::Mat4:		return 4 * 4 * 4;
			case TEngine::ShaderDataType::Int:		return 4;
			case TEngine::ShaderDataType::Int2:		return 4 * 2;
			case TEngine::ShaderDataType::Int3:		return 4 * 3;
			case TEngine::ShaderDataType::Int4:		return 4 * 4;
			case TEngine::ShaderDataType::Bool:		return 1;
		}

		TE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		bool Normalized;
		uint32_t Offset;
		uint32_t Size;

		BufferElement(ShaderDataType _type, const std::string& _name, bool _normalized = false) 
			: Name(_name), Type(_type), Normalized(_normalized), Offset(0), Size(ShaderDataTypeSize(_type)) 
		{

		}

		BufferElement()
			: Name("None"), Type(ShaderDataType::None), Normalized(false), Offset(0), Size(0) 
		{}

		uint32_t GetComponentCount() const 
		{
			switch (Type)
			{
				case TEngine::ShaderDataType::None:		break;
				case TEngine::ShaderDataType::Float:	return 1;
				case TEngine::ShaderDataType::Float2:	return 2;
				case TEngine::ShaderDataType::Float3:	return 3;
				case TEngine::ShaderDataType::Float4:	return 4;
				case TEngine::ShaderDataType::Mat3:		return 3 * 3;
				case TEngine::ShaderDataType::Mat4:		return 4 * 4;
				case TEngine::ShaderDataType::Int:		return 1;
				case TEngine::ShaderDataType::Int2:		return 2;
				case TEngine::ShaderDataType::Int3:		return 3;
				case TEngine::ShaderDataType::Int4:		return 4;
				case TEngine::ShaderDataType::Bool:		return 1;
			}

			TE_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}
	};

	class BufferLayout
	{
	public:

		BufferLayout(const std::initializer_list<BufferElement>& _elements)
			: m_Elements(_elements)
		{
			CalculateOffsetAndStride();
		}

		BufferLayout() {}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline const uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); } 
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }  
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); } 
	private:

		void CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size; 
				m_Stride += element.Size; 
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:

		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0; 

		virtual const BufferLayout& GetLayout() const = 0; 
		virtual void SetLayout(const BufferLayout& _layout) = 0; 

		static VertexBuffer* Create(float* _vertices, uint32_t _size);  
	};

	class IndexBuffer
	{
	public:

		virtual ~IndexBuffer() {} 

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* _indices, uint32_t _count); 
	};
}
