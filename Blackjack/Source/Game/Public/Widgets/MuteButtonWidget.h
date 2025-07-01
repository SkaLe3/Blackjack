#pragma once
#include <UISystem/Widgets/ToggleButtonWidget.h>
#include <Core/AssetManager.h>
#include <Sound/AudioSystem.h>
#include <Renderer/TextureAtlas.h>

class MuteButtonWidget : public Core::ToggleButtonWidget
{
	DECLARE_SUPER(ToggleButtonWidget)
public:
	MuteButtonWidget(const String& inName, const String& texture)
		: ToggleButtonWidget(inName)
	{
		SharedPtr<Core::Texture>  muteTex = Core::AssetManager::Get().Load<Core::TextureAsset>(texture)->TextureP;
		SharedPtr<Core::TextureAtlas> muteAtlas = MakeShared<Core::TextureAtlas>(muteTex);
		muteAtlas->AddRegion("mute_default", { 0, 0, 256, 256 });
		muteAtlas->AddRegion("mute_hover", { 256, 0, 256, 256 });
		muteAtlas->AddRegion("mute_press", { 0, 256, 256, 256 });
		muteAtlas->AddRegion("mute_active", { 256, 256, 256, 256 });

		SetAtlas(muteAtlas);
		SetRegion("mute_default");
		SetHoverImage(muteAtlas, "mute_hover");
		SetPressImage(muteAtlas, "mute_press");
		SetActiveImage(muteAtlas, "mute_active");

	}
};
