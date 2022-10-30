#pragma once

#include "Event/Event.h"
#include "Window.h"

#include "GUI/ImGui/ImGuiLayer.h"
#include "GUI/PanelStack.h"

namespace Morph {

	class Application
	{
	public:
		Application(const std::string& name);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
		
		virtual void OnUpdate(float timestep) {}
		virtual void OnDrawGUI() {}
		void OnEvent(Event& event);

		void Run();

		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
	protected:
		void AddPanel(const Ref<GUI::Panel>& panel);
	protected:
		PanelStack m_PanelStack;
	private:
		bool m_Running = true;
		float m_Time;
		Scope<Window> m_Window;

		Ref<ImGuiLayer> m_GUILayer;

		inline static Application* s_Instance = nullptr;
	};
}