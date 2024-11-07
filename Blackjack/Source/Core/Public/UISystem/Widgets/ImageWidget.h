#pragma once
#include "UISystem/Widget.h"

namespace Core
{
	class Sprite;
	class TextureAtlas;

	class ImageWidget : public Widget
	{
		DECLARE_SUPER(Widget)
	public:
		ImageWidget(const String& inName);

		virtual void OnPaint(SharedPtr<ScreenRenderer> renderer);

		virtual void Tick(float deltaTime);

		SharedPtr<Sprite> GetImage();
		SharedPtr<TextureAtlas> GetAtlas();
		glm::vec4 GetColor();
		bool HasAtlas();
		void UpdateAtlas();
		void SetFill(bool bFill);
		void SetColor(const glm::vec4& color);
		void SetImage(SharedPtr<Sprite> inSprite);
		void SetAtlas(SharedPtr<TextureAtlas> inAtlas);
		void SetRegion(const String& name);

	private:
		SharedPtr<Sprite> m_Image;
		SharedPtr<TextureAtlas> m_Atlas;
		glm::vec4 m_Color;
		bool m_bFill;
		bool m_bUseAtalas;
	};
}