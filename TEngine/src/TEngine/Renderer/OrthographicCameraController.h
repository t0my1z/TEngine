#pragma once

#include "TEngine/Renderer/OrthographicCamera.h"
#include "TEngine/Core/Timestep.h"
#include "TEngine/Events/ApplicationEvent.h"
#include "TEngine/Events/MouseEvent.h"

namespace TEngine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspecRatio, bool rotation = false); 

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; } 
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel; 
		OrthographicCamera m_Camera; 

		bool m_Rotation;
		glm::vec3 m_CameraPosition;
		float m_CameraRotation; 
		float m_CameraTranslationSpeed;
		float m_CameraRotationSpeed; 
	};
}
