#include "UISystem/Widgets/ImageWidget.h"
#include "Renderer/TextureAtlas.h"
#include "Renderer/Sprite.h"
#include "Renderer/ScreenRenderer.h"

namespace Core
{

	ImageWidget::ImageWidget(const String& inName)
		: Widget(inName), m_Image(nullptr), m_Atlas(nullptr), m_bUseAtalas(false), m_Color({ 1.0f, 1.0f, 1.0f, 1.0f }), m_bFill(true)
	{

	}

	void ImageWidget::OnPaint(SharedPtr<ScreenRenderer> renderer)
	{
		Super::OnPaint(renderer);
		if (m_bVisible)
		{
			AnchorData adata = GetParentRelatedAnchorData();
			if (m_Image)
			{
				renderer->DrawWidget(adata.Position, adata.Size, adata.Alignment, m_Image, m_Color);
			}
			else
			{
				renderer->DrawWidget(adata.Position, adata.Size, adata.Alignment, m_Color, m_bFill);
			}
		}
	}

	void ImageWidget::Tick(float deltaTime)
	{
		Super::Tick(deltaTime);
	}

	SharedPtr<Sprite> ImageWidget::GetImage()
	{
		return m_Image;
	}

	SharedPtr<TextureAtlas> ImageWidget::GetAtlas()
	{
		return m_Atlas;
	}

	glm::vec4 ImageWidget::GetColor()
	{
		return m_Color;
	}

	bool ImageWidget::HasAtlas()
	{
		return m_Atlas != nullptr;
	}

	void ImageWidget::UpdateAtlas()
	{
		m_Image->ChangeTexture(m_Atlas->GetTexture());
	}

	void ImageWidget::SetFill(bool bFill)
	{
		m_bFill = bFill;
	}

	void ImageWidget::SetColor(const glm::vec4& color)
	{
		m_Color = color;
	}

	void ImageWidget::SetColor(const glm::vec3& color)
	{
		m_Color = { color, m_Color.w };
	}

	void ImageWidget::SetAlpha(float alpha)
	{
		m_Color.w = alpha;
	}

	void ImageWidget::SetImage(SharedPtr<Sprite> inSprite)
	{
		if (!m_Atlas)
		{
			m_Image = inSprite;
		}
		else
		{
			BJ_ASSERT(false, "Cant change image when using Texture Atlas");
		}
	}

	void ImageWidget::SetAtlas(SharedPtr<TextureAtlas> inAtlas)
	{
		m_Atlas = inAtlas;
		m_Image = Sprite::Create(inAtlas->GetTexture());
	}

	void ImageWidget::SetRegion(const String& name)
	{
		glm::vec4 region = m_Atlas->GetRegion(name);
		m_Image->MapToAtlas(region);
	}

	void ImageWidget::SetHoverEnterSound(SharedPtr<SoundBase> sound)
	{
		m_HoverSound = sound;
	}

	void ImageWidget::SetHoverImage(SharedPtr<TextureAtlas> atlas, const String& name)
	{
		if (!m_DefaultImage)
		{
			m_DefaultImage = Sprite::Create(m_Atlas->GetTexture());
			*m_DefaultImage = *m_Image;
		}

		if (!m_HoverImage)
		{
			m_HoverImage = Sprite::Create(atlas->GetTexture());
		}
		else
		{
			m_HoverImage->ChangeTexture(atlas->GetTexture());
		}
		glm::vec4 region = atlas->GetRegion(name);
		m_HoverImage->MapToAtlas(region);
	}


	void ImageWidget::UseHoverVisuals()
	{
		if (m_HoverImage)
			m_Image = m_HoverImage;
	}

	void ImageWidget::UseDefaultVisuals()
	{
		if (m_DefaultImage)
			m_Image = m_DefaultImage;
	}

	void ImageWidget::UsePressVisuals()
	{
		if (m_PressImage)
			m_Image = m_PressImage;
	}

	void ImageWidget::UseActiveVisuals()
	{
		if (m_ActiveImage)
			m_Image = m_ActiveImage;
	}

}