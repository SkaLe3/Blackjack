#include "UISystem/Widgets/TextWidget.h"
#include "Renderer/ScreenRenderer.h"
#include "Renderer/Renderer.h"
#include "Core/Application.h"

namespace Core
{

	TextWidget::TextWidget(const String& inName)
		: Widget(inName), m_Color({ 1.0f, 1.0f, 1.0f, 1.0f })
	{
		m_FontID = "BebasNeue-Regular-32";
		m_Scale = 1.f;
	}

	void TextWidget::OnPaint(SharedPtr<ScreenRenderer> renderer)
	{
		Super::OnPaint(renderer);
		if (m_bVisible)
		{
			AnchorData adata = GetParentRelatedAnchorData();
			if (!m_Text.empty())
			{
				if (m_bDirty)
				{
					String activeFont = Renderer::Fonts->GetActiveFontID();
					if (activeFont != m_FontID)
					{
						bool bSelected = Renderer::Fonts->SelectFont(m_FontID);
					}
					m_CachedTextTexture = Renderer::Fonts->RenderText(m_Text, {m_Color.x, m_Color.y, m_Color.z, 1.0f});
					m_bDirty = false;
				}
				renderer->DrawTexture(adata.Position, m_CachedTextTexture->GetSize() * m_Scale, adata.Alignment, m_CachedTextTexture, {1.f, 1.f, 1.f, m_Color.w});
			}
		}
	}

	void TextWidget::SetFont(const String& fontID)
	{

		Font* newFont = Renderer::Fonts->GetFont(fontID);
		bool bLoaded = true;
		if (newFont == nullptr)
		{
			String fontName;
			String fontFullName;
			int32 fontSize;
			size_t pos = fontID.rfind('-');
			if (pos != String::npos)
			{
				fontFullName = fontID.substr(0, pos);
				fontSize = std::stoi(fontID.substr(pos+1, fontID.size()));
			}
			pos = fontID.find('-');
			if (pos != String::npos)
			{
				fontName = fontID.substr(0, pos);
			}

			bLoaded = Renderer::Fonts->AddFontFromFileTTF(fontID, "./Content/Fonts/" + fontName + "/" + fontFullName + ".ttf", fontSize);
		}
		if (bLoaded)
		{
			m_FontID = fontID;
		}
	}

	void TextWidget::SetText(const String& inText)
	{
		m_Text = inText;
		m_bDirty = true;
	}

	void TextWidget::SetColor(const glm::vec4& color)
	{
		m_Color = color;
	}

	void TextWidget::SetColor(const glm::vec3& color)
	{
		m_Color = { color, m_Color.w };
	}

	void TextWidget::SetAlpha(float alpha)
	{
		m_Color.w = alpha;
	}

	void TextWidget::SetScale(float textureScale)
	{
		m_Scale = glm::min(glm::max(0.f, textureScale), 1.f);
	}

	String TextWidget::GetText()
	{
		return m_Text;
	}

}