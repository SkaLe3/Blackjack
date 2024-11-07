#pragma once
#include "UISystem/Widgets/ImageWidget.h"
#include "Sound/Sound.h"

//SDL_BUTTON_LEFT     1
//SDL_BUTTON_MIDDLE   2
//SDL_BUTTON_RIGHT    3
//SDL_BUTTON_X1       4
//SDL_BUTTON_X2       5

DECLARE_DELEGATE_ONE_PARAM(ButtonPressedDelegate, int32)
DECLARE_DELEGATE_ONE_PARAM(ButtonReleasedDelegate, int32)
DECLARE_DELEGATE_ONE_PARAM(ButtonClickDelegate, int32)

namespace Core
{

	class ButtonWidget : public ImageWidget
	{
		DECLARE_SUPER(ImageWidget)
	public:
		ButtonWidget(const String& inName);

		virtual bool OnMouseMoved(Event& event, const glm::vec2& mousePos) override;
		virtual bool OnButtonDown(Event& event, const glm::vec2& mousePos) override;
		virtual bool OnButtonUp(Event& event, const glm::vec2& mousePos) override;

		void SetClickSound(SharedPtr<SoundBase> sound);
	public:
		ButtonPressedDelegate OnButtonPressed;
		ButtonReleasedDelegate OnButtonReleased;
		ButtonClickDelegate OnButtonClick;

	private:
		bool m_bHadPressBeforeRelease;
		SharedPtr<SoundBase> m_ClickSound;
	};
}