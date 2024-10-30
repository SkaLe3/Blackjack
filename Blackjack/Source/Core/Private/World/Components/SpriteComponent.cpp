#include "World/Components/SpriteComponent.h"

namespace Core
{

	SpriteComponent::SpriteComponent()
		: m_Sprite(nullptr), m_Atlas(nullptr), m_bUseAtlas(false)
	{

	}

	void SpriteComponent::Destroy()
	{
		// TODO: Delete from scene
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