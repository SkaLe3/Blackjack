#include "GameObjects/Chip.h"

#include <Core/AssetManager.h>
#include <Renderer/Sprite.h>

using namespace Core;

Chip::Chip()
{
	auto sprite = GetSpriteComponent();
	sprite->GetTransform().Scale = {10, 10, 1};
	sprite->SetSprite(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_Chip")->TextureP));
}

void Chip::BeginPlay()
{

}
