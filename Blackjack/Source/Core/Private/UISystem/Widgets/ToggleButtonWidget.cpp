#include "UISystem/Widgets/ToggleButtonWidget.h"

#include "Sound/AudioSystem.h"
#include "Renderer/Sprite.h"
#include "Renderer/TextureAtlas.h"

namespace Core
{

	ToggleButtonWidget::ToggleButtonWidget(const String& inName)
		: ButtonWidget(inName), m_Active(false)
	{
	}

	bool ToggleButtonWidget::OnMouseMoved(Event& event, const glm::vec2& mousePos)
	{
		bool bRes = Super::OnMouseMoved(event, mousePos);

		return bRes;
	}

	bool ToggleButtonWidget::OnButtonUp(Event& event, const glm::vec2& mousePos)
	{
		bool bRes = Super::OnButtonUp(event, mousePos);
		if (bRes)
		{
			m_Active = !m_Active;
			if (m_Active)
			{
				OnToggleEnabled.Broadcast(event.Ev.button.button);
			}
			else
			{
				OnToggleDisabled.Broadcast(event.Ev.button.button);
			}
		}
		UseDefaultVisuals();
		return bRes;
	}

	void ToggleButtonWidget::UseDefaultVisuals()
	{
		if (m_Active)
		{
			if (m_ActiveImage)
				m_Image = m_ActiveImage;
		}
		else
		{
			if (m_DefaultImage)
				m_Image = m_DefaultImage;
		}
	}

	void ToggleButtonWidget::UseHoverVisuals()
	{
		if (m_Active)
		{
			if (m_ActiveImage)
				m_Image = m_ActiveImage;
		}
		else
		{
			if (m_HoverImage)
				m_Image = m_HoverImage;
		}
	}

	void ToggleButtonWidget::SetActiveImage(SharedPtr<TextureAtlas> atlas, const String& name)
	{
		if (!m_DefaultImage)
		{
			m_DefaultImage = Sprite::Create(m_Atlas->GetTexture());
			*m_DefaultImage = *m_Image;
		}
		if (!m_ActiveImage)
		{
			m_ActiveImage = Sprite::Create(atlas->GetTexture());
		}
		else
		{
			m_ActiveImage->ChangeTexture(atlas->GetTexture());
		}
		glm::vec4 region = atlas->GetRegion(name);
		m_ActiveImage->MapToAtlas(region);
	}

	void ToggleButtonWidget::SetActivityState(bool bActive)
	{
		m_Active = bActive;
		UseDefaultVisuals();
	}

}