#include "Assets/CardTextureAtlas.h"
#include "Core/AssetManager.h"

using namespace Core;

CardTextureAtlas::CardTextureAtlas()
	: TextureAtlas(AssetManager::Get().Load<TextureAsset>("T_CardsAtlas")->TextureP)
{
	const char* suits[] = { "spades", "diamonds", "clubs", "hearts" };
	const char* ranks[] = { "2","3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			AddRegion(String(ranks[j]) + '_' + suits[i], { j * 400, i * 560, 400, 560 });
		}
	}
	AddRegion("back", { 13 * 400, 0 , 400, 560 });
}
