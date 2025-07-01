#pragma once
#include "UISystem/Widgets/ButtonWidget.h"

DECLARE_DELEGATE_ONE_PARAM(ToggleEnabledDelegate, int32)
DECLARE_DELEGATE_ONE_PARAM(ToggleDisabledDelegate, int32)

namespace Core
{
	class ToggleButtonWidget : public ButtonWidget
	{
		DECLARE_SUPER(ButtonWidget)
	public:
		ToggleButtonWidget(const String& inName);

		virtual bool OnMouseMoved(Event& event, const glm::vec2& mousePos) override;
		virtual bool OnButtonUp(Event& event, const glm::vec2& mousePos) override;
		virtual void UseDefaultVisuals() override;
		virtual void UseHoverVisuals() override;
		void SetActiveImage(SharedPtr<TextureAtlas> atlas, const String& region);
		void SetActivityState(bool bActive);
	public:
		ToggleEnabledDelegate OnToggleEnabled;
		ToggleDisabledDelegate OnToggleDisabled;

	private:
		bool m_Active;
	};
}