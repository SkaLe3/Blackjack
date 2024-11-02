#include "World/Components/SpriteComponent.h"

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
		m_Sprite = inSprite;
	}

	void SpriteComponent::SetAtlas(SharedPtr<TextureAtlas> inAtlas)
	{
		m_Atlas = inAtlas;
	}

}