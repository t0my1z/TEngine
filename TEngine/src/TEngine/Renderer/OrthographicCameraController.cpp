#include "tepch.h"
#include "OrthographicCameraController.h"
#include "TEngine/Core/Input.h" 
#include "TEngine/Core/KeyCodes.h"

namespace TEngine
{
	OrthographicCameraController::OrthographicCameraController(float aspecRatio, bool rotation)
		:
		m_AspectRatio(aspecRatio),
		m_ZoomLevel(1), 
		m_Camera(-m_AspectRatio * m_ZoomLevel /*Left*/, m_AspectRatio* m_ZoomLevel/*Right*/,
			-m_ZoomLevel /*Bottom*/, m_ZoomLevel /*Top*/),
		m_Rotation(rotation),
		m_CameraPosition(0.f), m_CameraRotation(0.f), m_CameraTranslationSpeed(5.f), m_CameraRotationSpeed(40.f)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		TE_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(TE_KEY_A))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(TE_KEY_D))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(TE_KEY_W))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(TE_KEY_S))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(TE_KEY_Q))
			{
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}
			if (Input::IsKeyPressed(TE_KEY_E))
			{
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}

			m_Camera.SetRotation(m_CameraRotation); 
		}

		m_Camera.SetPosition(m_CameraPosition); 
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		TE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e); 
		dispatcher.Dispatch<MouseScrolledEvent>(TE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));   
		dispatcher.Dispatch<WindowResizeEvent>(TE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));   
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		TE_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.5f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f); 
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel /*Left*/, m_AspectRatio * m_ZoomLevel/*Right*/,
			-m_ZoomLevel /*Bottom*/, m_ZoomLevel /*Top*/);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		TE_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight(); 
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel /*Left*/, m_AspectRatio * m_ZoomLevel/*Right*/, 
			-m_ZoomLevel /*Bottom*/, m_ZoomLevel /*Top*/); 
		return false;
	}
}