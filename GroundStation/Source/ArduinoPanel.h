#pragma once

#include "GUI/Panel.h"

#include "SerialPort.h"

using namespace Morph;

class ArduinoPanel : public GUI::Panel
{
public:
	ArduinoPanel()
		: Panel("Arduino Panel") {}
private:
	virtual void OnAttach() override
	{
		m_Arduino = CreateScope<SerialPort>(const_cast<char*>(m_Port));

		if (m_Arduino->IsConnected())
			MORPH_INFO("Connection established");
		else
			MORPH_ERROR("Connection failed");
	}

	virtual void OnDraw() override
	{
		ImVec2 btnSize = { 60, 30 };
		ImVec2 frameSize = ImGui::GetContentRegionAvail();
		frameSize.y -= btnSize.y;

		ImGui::BeginChildFrame(GetID(), frameSize);
		for (const std::string& log : m_LogStream)
			ImGui::Text(log.c_str());
		ImGui::EndChildFrame();
		
		if (ImGui::Button("On"))
		{
			m_Pressed = true;
			m_Command = "ON";
		}
		ImGui::SameLine();
		if (ImGui::Button("Off"))
		{
			m_Pressed = true;
			m_Command = "OFF";
		}
	}

	virtual void OnUpdate(float timestep) override
	{
		m_FrameTime = timestep;
		m_Timer += timestep;

		if (m_Arduino->IsConnected())
		{
			if (m_Arduino->ReadSerialPort(m_Input, MAX_DATA_LENGTH))
			{
				std::string input = m_Input;
				MORPH_INFO(m_Input);
				m_LogStream.push_back(input);
				for (int i = 0; i < MAX_DATA_LENGTH; i++)
					m_Input[i] = {};
			}

			if (m_Pressed)
			{
				m_Pressed = false;
				m_Arduino->WriteSerialPort(const_cast<char*>(m_Command.c_str()), MAX_DATA_LENGTH);
				MORPH_TRACE(m_Command);
			}

		}
	}
private:
	char m_Input[MAX_DATA_LENGTH]{};
	char m_Output[MAX_DATA_LENGTH]{};
	const char* m_Port = "\\\\.\\COM4";

	std::vector<std::string> m_LogStream;

	Scope<SerialPort> m_Arduino;
	std::string m_Command = "ON"; // On or Off
	bool m_Pressed = true;

	float m_Timer = 0.0f;
	float m_FrameTime = 0.0f;
};