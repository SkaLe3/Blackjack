#include "Assets/MenuButtonTextureAtlas.h"

#include "Core/AssetManager.h"

using namespace Core;

MenuButtonTextureAtlas::MenuButtonTextureAtlas()
	: TextureAtlas(AssetManager::Get().Load<TextureAsset>("T_Buttons")->TextureP)
{
	AddRegion("play_default", { 0, 0, 800, 160});
	AddRegion("leave_default", { 0, 160, 800, 160});
	AddRegion("addSkin_default", { 0, 320, 800, 160});
	AddRegion("play_press", { 800, 0, 800, 160 });
	AddRegion("leave_press", { 800, 160, 800, 160 });
	AddRegion("addSkin_press", { 800, 320, 800, 160 });
	AddRegion("play_hover", { 0, 0 + 480, 800, 160 });
	AddRegion("leave_hover", { 0, 160 + 480, 800, 160 });
	AddRegion("addSkin_hover", { 0, 320 + 480, 800, 160 });
}
