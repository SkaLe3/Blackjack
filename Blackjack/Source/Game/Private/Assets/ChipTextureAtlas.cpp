#include "Assets/ChipTextureAtlas.h"
#include <Core/AssetManager.h>

using namespace Core;

ChipTextureAtlas::ChipTextureAtlas()
	: ChipTextureAtlas(AssetManager::Get().Load<TextureAsset>("T_ChipAtlas")->TextureP)
{

}

ChipTextureAtlas::ChipTextureAtlas(SharedPtr<Core::Texture> texture)  : TextureAtlas(texture)
{
	AddRegion("white", { 0 * 280, 0 * 280, 280, 280 });
	AddRegion("red", { 1 * 280, 0 * 280, 280, 280 });
	AddRegion("blue", { 2 * 280, 0 * 280, 280, 280 });
	AddRegion("gray", { 0 * 280, 1 * 280, 280, 280 });
	AddRegion("green", { 1 * 280, 1 * 280, 280, 280 });
	AddRegion("orange", { 2 * 280, 1 * 280, 280, 280 });
}
