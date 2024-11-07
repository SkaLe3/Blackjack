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
				renderer->DrawWidget(adata.Position, adata.Size, adata.Alignment, m_Image);
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

	void ImageWidget::SetImage(SharedPtr<Sprite> inSprite)
	{
		if (!m_Atlas)
		{
			m_Image = inSprite ;
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

}