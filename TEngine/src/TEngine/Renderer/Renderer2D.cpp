#include "tepch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>

namespace TEngine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;  
		Ref<Texture2D> WhiteTexture2D;  
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		TE_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();  

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
		};

		Ref<TEngine::VertexBuffer> vertexB;
		vertexB = VertexBuffer::Create(vertices, sizeof(vertices));
		vertexB->SetLayout
		(
			{
				{ ShaderDataType::Float3, "a_Position"}, 
				{ ShaderDataType::Float2, "a_TexCoord"}  
			}
		);

		s_Data->QuadVertexArray->AddVertexBuffer(vertexB); 

		uint32_t indices[6] = { 0, 1, 2, 1, 2, 3 };
		Ref<IndexBuffer> indexB;
		indexB = IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(indexB); 

		s_Data->WhiteTexture2D = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff; 
		s_Data->WhiteTexture2D->SetData(&whiteTextureData, sizeof(uint32_t));  

		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl"); 
		s_Data->TextureShader->Bind(); 
		s_Data->TextureShader->SetInt("u_Texture", 0);  
	}

	void Renderer2D::Shutdown()
	{
		TE_PROFILE_FUNCTION(); 

		delete s_Data; 
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		TE_PROFILE_FUNCTION();

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}						 

	void Renderer2D::EndScene()
	{
		TE_PROFILE_FUNCTION();

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{ 
		DrawQuad({ position.x, position.y, 0 }, size, color);  
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		TE_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("u_Color", color); 
		s_Data->WhiteTexture2D->Bind(); 

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		s_Data->TextureShader->SetMat4("u_Transform", transform); 
		 
		s_Data->QuadVertexArray->Bind(); 
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);  
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0 }, size, texture);  
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		TE_PROFILE_FUNCTION(); 

		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1));  
		texture->Bind(); 
		 
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform); 
		 
		s_Data->QuadVertexArray->Bind(); 
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray); 
	}
}