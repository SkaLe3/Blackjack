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
		void SetColor(const glm::vec3& color);
		void SetAlpha(float alpha);
		void SetImage(SharedPtr<Sprite> inSprite);
		void SetAtlas(SharedPtr<TextureAtlas> inAtlas);
		void SetRegion(const String& name);

		void SetHoverEnterSound(SharedPtr<SoundBase> sound);
		void SetHoverImage(SharedPtr<TextureAtlas> atlas, const String& region);

	protected:
		virtual void UseHoverVisuals() override;
		virtual void UseDefaultVisuals() override;
		virtual void UsePressVisuals() override;
		virtual void UseActiveVisuals() override;
	protected:
		SharedPtr<Sprite> m_DefaultImage;
		SharedPtr<Sprite> m_HoverImage;
		SharedPtr<Sprite> m_PressImage;
		SharedPtr<Sprite> m_ActiveImage;
		SharedPtr<Sprite> m_Image;
		SharedPtr<TextureAtlas> m_Atlas;
	private:
		glm::vec4 m_Color;
		bool m_bFill;
		bool m_bUseAtalas;
	};
}