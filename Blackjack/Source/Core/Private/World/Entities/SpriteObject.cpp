#include  "World/Entities/SpriteObject.h"
#include "World/Components/SpriteComponent.h"
#include "Renderer/Sprite.h"

namespace Core
{

	SpriteObject::SpriteObject()
	{
		m_SpriteComponent = CreateComponent<SpriteComponent>();
		auto sprite = GetSpriteComponent();
		sprite->SetupAttachment(GetBoxComponent());
		sprite->SetOwner(GetSelf());
		// Note: Texture Atlas (and Sprite) should be set by GameMode or by Deck during game start
		//		to use one Atlas instance across all cards.
		//		However Sprite cannot use flyweight pattern
		//		because it stores coordinates of texture source.
		//		But still all sprites will use the same Texture instance
	}

}