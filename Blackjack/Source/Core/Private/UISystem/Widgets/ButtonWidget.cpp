#include "UISystem/Widgets/ButtonWidget.h"

#include "Sound/AudioSystem.h"

namespace Core
{

	ButtonWidget::ButtonWidget(const String& inName)
		: ImageWidget(inName), m_bHadPressBeforeRelease(false)
	{

	}


	bool ButtonWidget::OnMouseMoved(Event& event, const glm::vec2& mousePos)
	{
		ProvideMousePos(mousePos);
		if (!m_bHovered)
		{
			m_bHadPressBeforeRelease = false;
		}
		return false;
	}

	bool ButtonWidget::OnButtonDown(Event& event, const glm::vec2& mousePos)
	{
		ProvideMousePos(mousePos);
		if (m_bHovered)
		{
			OnButtonPressed.Broadcast(event.Ev.button.button);

			m_bHadPressBeforeRelease = true;
			return true;
		}
		return false;
	}

	bool ButtonWidget::OnButtonUp(Event& event, const glm::vec2& mousePos)
	{
		if (m_bHovered)
		{
			OnButtonReleased.Broadcast(event.Ev.button.button);
			if (m_bHadPressBeforeRelease)
			{
				OnButtonClick.Broadcast(event.Ev.button.button);
				if (m_ClickSound)
					AudioSystem::PlaySound(m_ClickSound);
			}
			m_bHadPressBeforeRelease = false;
			return true;
		}
		return false;

	}

	void ButtonWidget::SetClickSound(SharedPtr<SoundBase> sound)
	{
		 m_ClickSound = sound;
	}

}