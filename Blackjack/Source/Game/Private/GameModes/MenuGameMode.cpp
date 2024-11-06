#include <GameModes/MenuGameMode.h>
#include <World/Entities/GameObject.h>
#include <World/World/World.h>
#include <Core/AssetManager.h>
#include <Renderer/Sprite.h>
#include <World/Entities/CameraObject.h>
#include <Scenes/GameplayScene.h>
#include <Core/Utils.h>

#include <filesystem>

using namespace Core;

void MenuGameMode::BeginPlay()
{
	RestartMenu();
}

void MenuGameMode::OnEvent(Core::Event& event)
{
	if (event.Ev.type == SDL_KEYDOWN)
	{
		if (event.Ev.key.keysym.sym == SDLK_o)
		{
			String filepath = FileDialogs::OpenFile("PNG Files\0*.PNG\0All Files\0*.*\0");
			if (!filepath.empty())
			{
				BJ_LOG_INFO("Found file: %s", filepath.c_str());
				std::filesystem::path source = filepath;
				std::filesystem::path destinationDir = std::filesystem::current_path()/ AssetManager::Get().GetContentPath() / "Textures";
				std::filesystem::path destination = destinationDir / source.filename();
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
	}
}

void MenuGameMode::RestartMenu()
{
	// 	SharedPtr<GameObject> chip = GetWorld()->SpawnGameObject<GameObject>();
	// 	chip->SetTag("Chip");
	// 	SharedPtr<SpriteComponent> sprite = chip->CreateComponent<SpriteComponent>();
	// 	sprite->SetupAttachment(chip->GetBoxComponent());
	// 	SharedPtr<Texture> chipTex = AssetManager::Get().Load<TextureAsset>("T_RedChip")->TextureP;
	// 	sprite->SetSprite(MakeShared<Sprite>(chipTex));
	// 
	// 	sprite->SetOwner(chip);
	// 	sprite->GetTransform().Scale = { 5.f, 5.f, 1.0f };
	// 	chip->GetTransform().Translation = {2, 0, 1};
	// 
	// 	SharedPtr<GameObject> card = GetWorld()->SpawnGameObject<GameObject>();
	// 	card->SetTag("Carad");
	// 	SharedPtr<SpriteComponent> sprite2 = card->CreateComponent<SpriteComponent>();
	// 	sprite2->SetupAttachment(card->GetBoxComponent());
	// 	SharedPtr<Texture> cardText = AssetManager::Get().Load<TextureAsset>("T_CardKing")->TextureP;
	// 	sprite2->SetSprite(MakeShared<Sprite>(cardText));
	// 
	// 	sprite2->SetOwner(card);
	// 	sprite2->GetTransform().Scale = {5.f, 5.f, 1.f};
	// 	card->GetTransform().Translation = {5, 0, 2};
	// 
	// 	SharedPtr<BoxComponent> box = chip->GetBoxComponent();

	SharedPtr<CameraObject> camera = GetWorld()->SpawnGameObject<CameraObject>();

	auto cameraComp = camera->GetCameraComponent();
	cameraComp->GetCamera()->SetOrthoSize(10);

}

void MenuGameMode::StartGame()
{
	World::OpenScene<GameplayScene>();
}
