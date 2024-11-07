#include <GameModes/MenuGameMode.h>
#include <World/Entities/GameObject.h>
#include <World/World/World.h>
#include <Core/AssetManager.h>
#include <Renderer/Sprite.h>
#include <World/Entities/CameraObject.h>
#include <Scenes/GameplayScene.h>
#include <Core/Utils.h>
#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>

#include "Widgets/MenuWidgetLayout.h"

#include <filesystem>

using namespace Core;

void MenuGameMode::BeginPlay()
{
	RestartMenu();
	SharedPtr<SoundBase> music = AssetManager::Get().Load<SoundAsset>("S_Music2")->SoundP;
	music->SetOneShot(false);
	AudioSystem::PlayMusic(music, 0.3f);

}

void MenuGameMode::OnEvent(Core::Event& event)
{
	if (event.Ev.type == SDL_KEYDOWN)
	{
		if (event.Ev.key.keysym.sym == SDLK_o)
		{
			AddSkin();
		}
	}
}

void MenuGameMode::RestartMenu()
{

	SharedPtr<CameraObject> camera = GetWorld()->SpawnGameObject<CameraObject>();

	auto cameraComp = camera->GetCameraComponent();
	cameraComp->GetCamera()->SetOrthoSize(10);

	CreateMenuWidget();

}

void MenuGameMode::StartGame()
{
	World::OpenScene<GameplayScene>();
}

void MenuGameMode::AddSkin()
{
	/*
	* Files with the "Skin_" prefix are considered texture atlases for card skins.
	* Use images from the Content/Files folder to load them as skins;
	* the prefix will be added automatically.
	*/
	String filepath = FileDialogs::OpenFile("PNG Files\0*.PNG\0All Files\0*.*\0");
	if (!filepath.empty())
	{
		BJ_LOG_INFO("Found file: %s", filepath.c_str());
		std::filesystem::path source = filepath;
		std::filesystem::path destinationDir = std::filesystem::current_path() / AssetManager::Get().GetContentPath() / "Textures";

		std::string filename = source.filename().string();
		const std::string prefix = "Skin_";

		if (filename.rfind(prefix, 0) != 0)
		{	// If filename doesn't start with "Skin_"
			filename = prefix + filename;      // Add prefix
		}
		std::filesystem::path destination = destinationDir / filename;
		AssetManager::Get().Register(destination);

		try
		{
			std::filesystem::copy_file(source, destination, std::filesystem::copy_options::overwrite_existing);
			BJ_LOG_INFO("File copied successfully to: %s", destination.string().c_str());
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			BJ_LOG_ERROR("%s", e.what());
		}
	}
	else
	{
		BJ_LOG_WARN("Couldn't open file %s", filepath.c_str());
	}
}

void MenuGameMode::CreateMenuWidget()
{
	if (SharedPtr<MenuWidgetLayout> myWidget = CreateWidgetLayout<MenuWidgetLayout>("Menu"))
	{
		auto clickSound = AssetManager::Get().Load<SoundAsset>("S_BtnLightClick")->SoundP;
		myWidget->Init();
		myWidget->AddToViewport(1);
		myWidget->StartButton.lock()->OnButtonClick.Add([=](int32 button) { StartGame(); });
		myWidget->LeaveButton.lock()->OnButtonClick.Add([=](int32 button) { LeaveGame(); });
		myWidget->AddSkinButton.lock()->OnButtonClick.Add([=](int32 button) { AddSkin(); });
		myWidget->StartButton.lock()->SetClickSound(clickSound);
		myWidget->LeaveButton.lock()->SetClickSound(clickSound);
		myWidget->AddSkinButton.lock()->SetClickSound(clickSound);
	}
}
