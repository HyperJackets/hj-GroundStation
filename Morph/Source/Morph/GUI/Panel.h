#pragma once

#include "Core/UUID.h"
#include "Application/Layer/Layer.h"

#include <imgui.h>

namespace Morph::GUI {
	
	class Panel : public Layer
	{
	private:
		inline static uint64 s_IDCounter = 1;
	public:
		Panel(const char* name)
			: Layer(name) 
		{
			m_UniqueName = name;
			m_ID = s_IDCounter++;
			m_UniqueName += "####" + std::to_string(m_ID);
		}

		void Open()  { m_IsOpen = true;  }
		void Close() { m_IsOpen = false; }

		bool IsOpen() const { return m_IsOpen; }

		UUID GetID() const { return m_ID; }

		virtual void OnRenderGUI() override final
		{
			if (m_IsOpen)
			{
				ImGui::PushID(GetID());
				ImGui::Begin(m_UniqueName.c_str(), &m_IsOpen);

				OnDraw();

				ImGui::End();
				ImGui::PopID();
			}
		}
	protected:
		/**
		* Methods to be used by user-defined panels
		*/

		virtual void OnDraw() {}
	private:
		bool m_IsOpen = true;

		UUID m_ID;
		std::string m_UniqueName;
	};

}