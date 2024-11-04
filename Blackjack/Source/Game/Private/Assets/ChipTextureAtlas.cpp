#include "Assets/ChipTextureAtlas.h"
#include <Core/AssetManager.h>

using namespace Core;

ChipTextureAtlas::ChipTextureAtlas()
	: TextureAtlas(AssetManager::Get().Load<TextureAsset>("T_ChipAtlas")->TextureP)
{
	AddRegion("white", { 0 * 280, 0 * 280, 280, 280 });
	AddRegion("red",   { 1 * 280, 0 * 280, 280, 280 });
	AddRegion("blue",  { 2 * 280, 0 * 280, 280, 280 });
	AddRegion("gray",  { 0 * 280, 1 * 280, 280, 280 });
	AddRegion("green", { 1 * 280, 1 * 280, 280, 280 });
	AddRegion("orange",{ 2 * 280, 1 * 280, 280, 280 });
}
