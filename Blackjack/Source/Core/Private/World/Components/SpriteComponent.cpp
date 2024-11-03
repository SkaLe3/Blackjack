#include "World/Components/SpriteComponent.h"

#include "Renderer/TextureAtlas.h"
#include "Renderer/Sprite.h"

namespace Core
{

	SpriteComponent::SpriteComponent()
		: m_Sprite(nullptr), m_Atlas(nullptr), m_bUseAtlas(false)
	{

	}

	bool SpriteComponent::HasAtlas()
	{
		return m_Atlas != nullptr;
	}

	SharedPtr<Sprite> SpriteComponent::GetSprite()
	{
		return m_Sprite;
	}

	SharedPtr<TextureAtlas> SpriteComponent::GetAtlas()
	{
		return m_Atlas;
	}

	void SpriteComponent::SetSprite(SharedPtr<Sprite> inSprite)
	{
		if (!m_Atlas)
		{
			m_Sprite = inSprite;
		}
		else
		{
			BJ_ASSERT(false, "Cant change sprite when using Texture Atlas");
		}
	}

	void SpriteComponent::SetAtlas(SharedPtr<TextureAtlas> inAtlas)
	{
		m_Atlas = inAtlas;
		m_Sprite = Sprite::Create(inAtlas->GetTexture());
	}

	void SpriteComponent::SetRegion(const String& name)
	{
		glm::vec4 region = m_Atlas->GetRegion(name);
		m_Sprite->MapToAtlas(region);
	}

}