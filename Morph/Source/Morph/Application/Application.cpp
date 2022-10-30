#include "Application.h"

#include "Window.h"
#include "Event/EventDispatcher.h"

#include "GUI/Layout.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>

namespace Morph {

	Application::Application(const std::string& name)
	{
		s_Instance = this;

		m_Window = Window::Create(name, 1920, 1080, true);
		m_Window->SetEventCallback(CALLBACK_BIND(OnEvent));
		m_GUILayer = CreateRef<ImGuiLayer>(); 

		m_Time = 0.0f;
	}

	void Application::Run()
	{
		m_GUILayer->OnAttach();

		OnAttach();

		for (auto& panel : m_PanelStack)
			panel->OnAttach();

		while (m_Running)
		{
			float currTime = (float)glfwGetTime();
			float timestep = currTime - m_Time;
			m_Time = currTime;

			glClearColor(0.8, 0.2, 0.2, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);

			OnUpdate(timestep);

			for (auto& panel : m_PanelStack)
			{
				panel->OnUpdate(timestep);
			}

			m_GUILayer->Begin();

			Layout::BeginDockspace();

			OnDrawGUI();

			for (auto& panel : m_PanelStack)
			{
				panel->OnRenderGUI();
			}

			Layout::EndDockspace();

			m_GUILayer->End();

			m_Window->OnUpdate();
		}

		for (auto& panel : m_PanelStack)
			panel->OnDetach();

		OnDetach();

		m_GUILayer->OnDetach();
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<EventType::WindowClose>(EVENT_BIND(WindowCloseEvent, OnWindowClose));
		dispatcher.Dispatch<EventType::WindowResize>(EVENT_BIND(WindowResizeEvent, OnWindowResize));

		if (!event.Handled)
			m_GUILayer->OnEvent(event);

		//std::string eventName = event.GetName();
		//MORPH_INFO(event.GetName());
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return false;
	}

	void Application::AddPanel(const Ref<GUI::Panel>& panel)
	{
		m_PanelStack.PushPanel(panel);
	}
}