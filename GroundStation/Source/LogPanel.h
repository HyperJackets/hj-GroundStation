#pragma once

#include "GUI/Panel.h"

#include "SerialPort.h"

using namespace Morph;

class ArduinoPanel : public GUI::Panel
{
public:
	ArduinoPanel()
		: Panel("Log Panel") {}
private:
	virtual void OnDraw() override
	{
		ImVec2 btnSize = { 60, 30 };
		ImVec2 frameSize = ImGui::GetContentRegionAvail();
		frameSize.y -= btnSize.y;

		ImGui::BeginChildFrame(GetID(), frameSize);
		for (const std::string& log : m_Logs)
			ImGui::Text(log.c_str());
		ImGui::EndChildFrame();

		if (ImGui::Button("Enter", btnSize))
		{
			m_Logs.push_back(m_InputBuffer);
			for (int i = 0; i < 128; i++)
				m_InputBuffer[i] = {};
		}

		ImGui::SameLine();

		ImGui::InputText("##", m_InputBuffer, 128);
	}
private:
	char m_InputBuffer[128]{};
	std::vector<std::string> m_Logs;

};