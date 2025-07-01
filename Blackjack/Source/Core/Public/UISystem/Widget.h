#pragma once
#include "Core/CoreDefines.h"

#include "UISystem/PanelSlot.h"
#include "Core/Event.h"
#include "Sound/Sound.h"

DECLARE_DELEGATE_NO_PARAMS(WidgetBeginHoverDelegate)
DECLARE_DELEGATE_NO_PARAMS(WidgetEndHoverDelegate)

namespace Core
{
	class PanelWidget;
	class PanelSlot;
	class ViewportSystem;
	class ScreenRenderer;
	class TextureAtlas;

	class Widget : public std::enable_shared_from_this<Widget>
	{
		friend ViewportSystem;
	public:
		Widget(const String& inName) : m_Name(inName) {}
		virtual ~Widget() = default;

		virtual void Init(){}

		virtual void OnPaint(SharedPtr<ScreenRenderer> renderer);
		AnchorData GetParentRelatedAnchorData();

		String GetName() { return m_Name; }
		inline SharedPtr<Widget> GetSelf() { return shared_from_this(); }

		void SetHover(bool inHovered) { m_bHovered = inHovered; }
		bool IsHovered() const { return m_bHovered; }

		void SetVisibility(bool bVisible) { m_bVisible = bVisible; }
		bool IsVisible()const { return m_bVisible; }

		SharedPtr<PanelWidget> GetParent() const;
		virtual void RemoveFromParent();
	public:
		virtual void Tick(float deltaTime);
		virtual bool OnMouseMoved(Event& event, const glm::vec2& mousePos);
		virtual bool OnButtonDown(Event& event, const glm::vec2& mousePos);
		virtual bool OnButtonUp(Event& event, const glm::vec2& mousePos);
		virtual bool OnHoverEnter();
		virtual bool OnHoverExit();

		virtual bool ProvideMousePos(const glm::vec2& mousePos);
		void SetHoverSound(SharedPtr<SoundBase> sound);
	protected:
		virtual void UseHoverVisuals();
		virtual void UseDefaultVisuals();
		virtual void UsePressVisuals();
		virtual void UseActiveVisuals();
	public:
		WidgetBeginHoverDelegate OnBeginHover;
		WidgetEndHoverDelegate OnEndHover;

	public:
		SharedPtr<PanelSlot> Slot;

	protected:
		SharedPtr<SoundBase> m_HoverSound;
	protected:
		String m_Name;
		bool m_bManagedByViewportSystem;
		bool m_bHovered = false;
		bool m_bVisible = true;
	};
}