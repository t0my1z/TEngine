#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Renderer/Shader.h"

namespace TEngine
{
	class Renderer
	{
	public:

		static void BeginScene(OrthographicCamera& camera);  
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& _vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}