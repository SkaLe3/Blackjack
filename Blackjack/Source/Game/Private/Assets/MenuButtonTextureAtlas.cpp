#include "Assets/MenuButtonTextureAtlas.h"

#include "Core/AssetManager.h"

using namespace Core;

MenuButtonTextureAtlas::MenuButtonTextureAtlas()
	: TextureAtlas(AssetManager::Get().Load<TextureAsset>("T_Buttons")->TextureP)
{
	AddRegion("play", { 0, 0, 800, 160});
	AddRegion("leave", { 0, 160, 800, 160});
}
