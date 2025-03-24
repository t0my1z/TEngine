#include "tepch.h"
#include "ImGuiLayer.h"
#include "Platforms_Windows/OpenGL/ImGuiOpenGLRenderer.h"
#include "TEngine/Application.h"


#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace TEngine
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos; 

		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO(); 
		Application& App = Application::Get(); 
		io.DisplaySize = ImVec2(App.GetWindow().GetWidth(), App.GetWindow().GetHeight()); 

		float time = (float)glfwGetTime();  
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.f / 60.f); 
		m_Time = time; 
		 
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();  

		static bool show = true;
		ImGui::ShowDemoWindow(&show); 

		ImGui::Render(); 
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& _event)
	{
		EventDispatcher dispatcher(_event); 
		dispatcher.Dispatch<MouseButtonPressedEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent)); 
		dispatcher.Dispatch<MouseButtonReleasedEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent)); 
		dispatcher.Dispatch<MouseMovedEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent)); 
		dispatcher.Dispatch<MouseScrolledEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent)); 
		dispatcher.Dispatch<KeyPressedEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent)); 
		dispatcher.Dispatch<KeyTypedEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent)); 
		dispatcher.Dispatch<KeyReleasedEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent)); 
		dispatcher.Dispatch<WindowResizeEvent>(TE_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO(); 
		io.MouseDown[_event.GetMouseButton()] = true; 

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[_event.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(_event.GetX(), _event.GetY());   

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += _event.GetXOffset(); 
		io.MouseWheel += _event.GetYOffset();  

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[_event.GetKeyCode()] = true; 

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[_event.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = _event.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& _event) 
	{
		ImGuiIO& io = ImGui::GetIO(); 
		io.DisplaySize = ImVec2(_event.GetWidth(), _event.GetHeight()); 
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f); 
		glViewport(0, 0, _event.GetWidth(), _event.GetHeight()); 

		return false;
	}
}
