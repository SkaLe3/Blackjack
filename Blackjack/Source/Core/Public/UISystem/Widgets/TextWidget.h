#pragma once
#include "UISystem/Widget.h"
#include "Renderer/Font.h"

namespace Core
{
	class TextWidget : public Widget
	{
		DECLARE_SUPER(Widget)
	public:
		TextWidget(const String& inName);

		virtual void OnPaint(SharedPtr<ScreenRenderer> renderer);

		void SetFont(const String& fontID);
		void SetText(const String& inText);
		void SetColor(const glm::vec4& color);
		void SetColor(const glm::vec3& color);
		void SetAlpha(float alpha);
		void SetScale(float textureScale);
		String GetText();
	private:
		SharedPtr<Texture> m_CachedTextTexture;
		String m_FontID;
		String m_Text;
		glm::vec4 m_Color;
		float m_Scale;
		bool m_bDirty;

	};
}