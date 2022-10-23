#include <Application/EntryPoint.h>
#include <GUI/PanelStack.h>
#include <GUI/Layout.h>
#include <GUI/Style.h>

#include "ArduinoPanel.h"

using namespace Morph;

class GroundStationApp : public Application
{
public:
	GroundStationApp(const std::string& name)
		: Application(name), m_Font("Montserrat")
	{
		m_PanelStack.PushPanel(CreateRef<ArduinoPanel>());
		for (auto& panel : m_PanelStack)
			panel->OnAttach();

	}

	virtual void OnDrawGUI() override
	{
		Layout::BeginDockspace();

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("View"))
			{
				for (auto& panel : m_PanelStack)
				{
					if (ImGui::MenuItem(panel->GetName(), panel->IsOpen() ? "Close" : "Open"))
					{
						if (panel->IsOpen())
							panel->Close();
						else
							panel->Open();
					}
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Stats");
		ImGui::Text("%.3f ms", m_FrameTime * 1000.0f);
		ImGui::Text("%.2f fps", 1.0f / m_FrameTime);
		ImGui::End();

		for (auto& panel : m_PanelStack)
		{
			panel->OnRenderGUI();
		}

		Layout::EndDockspace();
	}

	virtual void OnUpdate(float timestep) override
	{
		m_FrameTime = timestep;
		for (auto& panel : m_PanelStack)
			panel->OnUpdate(timestep);
	}
private:
	float m_FrameTime = 0.0f;
	PanelStack m_PanelStack;
	Font m_Font;
};

Application* CreateApplication()
{
	return new GroundStationApp("HyperJackets | Ground Station");
}