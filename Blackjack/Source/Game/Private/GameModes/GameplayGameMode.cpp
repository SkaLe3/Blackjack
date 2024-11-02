#include "GameModes/GameplayGameMode.h"
#include "World/Entities/GameObject.h"
#include "World/World/World.h"
#include "Core/AssetManager.h"
#include "Renderer/Sprite.h"
#include "World/Entities/CameraObject.h"

#include "Scenes/MenuScene.h"

using namespace Core;

void GameplayGameMode::BeginPlay()
{
	RestartGame();
}

void GameplayGameMode::RestartGame()
{
	SharedPtr<GameObject> card = GetWorld()->SpawnGameObject<GameObject>();
	card->SetTag("Carad");
	SharedPtr<SpriteComponent> sprite2 = card->CreateComponent<SpriteComponent>();
	sprite2->SetupAttachment(card->GetBoxComponent());
	SharedPtr<Texture> cardText = AssetManager::Get().Load<TextureAsset>("T_CardBlackSkin")->TextureP;
	sprite2->SetSprite(MakeShared<Sprite>(cardText));

	sprite2->SetOwner(card);
	sprite2->GetTransform().Scale = { 5.f, 5.f, 1.f };
	card->GetTransform().Translation = { 5, 0, 2 };

	SharedPtr<CameraObject> camera = GetWorld()->SpawnGameObject<CameraObject>();

	auto cameraComp = camera->GetCameraComponent();
	cameraComp->GetCamera()->SetOrthoSize(100);
}											  

void GameplayGameMode::LeaveGame()
{
	World::OpenScene<MenuScene>();
}
