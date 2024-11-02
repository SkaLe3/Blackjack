#include "GameModes/MenuGameMode.h"
#include "World/Entities/GameObject.h"
#include "World/World/World.h"
#include "Core/AssetManager.h"
#include "Renderer/Sprite.h"
#include "World/Entities/CameraObject.h"
#include "Scenes/GameplayScene.h"

using namespace Core;

void MenuGameMode::BeginPlay()
{
	
	RestartMenu();
}

void MenuGameMode::RestartMenu()
{
	SharedPtr<GameObject> chip = GetWorld()->SpawnGameObject<GameObject>();
	chip->SetTag("Chip");
	SharedPtr<SpriteComponent> sprite = chip->CreateComponent<SpriteComponent>();
	sprite->SetupAttachment(chip->GetBoxComponent());
	SharedPtr<Texture> chipTex = AssetManager::Get().Load<TextureAsset>("T_RedChip")->TextureP;
	sprite->SetSprite(MakeShared<Sprite>(chipTex));

	sprite->SetOwner(chip);
	sprite->GetTransform().Scale = { 5.f, 5.f, 1.0f };
	chip->GetTransform().Translation = {2, 0, 1};

	SharedPtr<GameObject> card = GetWorld()->SpawnGameObject<GameObject>();
	card->SetTag("Carad");
	SharedPtr<SpriteComponent> sprite2 = card->CreateComponent<SpriteComponent>();
	sprite2->SetupAttachment(card->GetBoxComponent());
	SharedPtr<Texture> cardText = AssetManager::Get().Load<TextureAsset>("T_CardKing")->TextureP;
	sprite2->SetSprite(MakeShared<Sprite>(cardText));

	sprite2->SetOwner(card);
	sprite2->GetTransform().Scale = {5.f, 5.f, 1.f};
	card->GetTransform().Translation = {5, 0, 2};

	SharedPtr<BoxComponent> box = chip->GetBoxComponent();

	SharedPtr<CameraObject> camera = GetWorld()->SpawnGameObject<CameraObject>();

	auto cameraComp = camera->GetCameraComponent();
	cameraComp->GetCamera()->SetOrthoSize(10);

}

void MenuGameMode::StartGame()
{
	World::OpenScene<GameplayScene>();
}
