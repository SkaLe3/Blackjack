#include "GameModes/GameplayGameMode.h"

#include "Scenes/MenuScene.h"
#include "GameObjects/Deck.h"
#include "GameObjects/Chip.h"

#include <Core/AssetManager.h>
#include <World/World/World.h>
#include <World/Entities/SpriteObject.h>
#include <World/Entities/CameraObject.h>

#include "Renderer/Sprite.h"

#include <glm/ext/scalar_constants.hpp>

using namespace Core;

void GameplayGameMode::BeginPlay()
{
	RestartGame();
}

void GameplayGameMode::RestartGame()
{


	SharedPtr<CameraObject> camera = GetWorld()->SpawnGameObject<CameraObject>();

	auto cameraComp = camera->GetCameraComponent();
	cameraComp->GetCamera()->SetOrthoSize(100);

	SharedPtr<SpriteObject> table = GetWorld()->SpawnGameObject<SpriteObject>();
	table->GetSpriteComponent()->SetSprite(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_Table")->TextureP));
	table->GetTransform().Translation.z = -200;
	table->GetSpriteComponent()->GetTransform().Scale = { 177, 100, 1 };

	auto deck = GetWorld()->SpawnGameObject<Deck>();
	deck->PopulateDeck();
	deck->GetTransform().Translation = { -60, 26, -100 };

	auto chip = GetWorld()->SpawnGameObject<Chip>();
	auto chip2 = GetWorld()->SpawnGameObject<Chip>();
	chip2->SetLocation({ 0, 1 });
	auto chip3 = GetWorld()->SpawnGameObject<Chip>();
	chip3->SetLocation({ 0, 2 });
	auto chip4 = GetWorld()->SpawnGameObject<Chip>();
	chip4->SetLocation({ 0, 3 });
	auto chip5 = GetWorld()->SpawnGameObject<Chip>();
	chip5->SetLocation({ 0, 4 });
	auto chip6 = GetWorld()->SpawnGameObject<Chip>();
	chip6->SetLocation({ 0, 5 });



}

void GameplayGameMode::LeaveGame()
{
	World::OpenScene<MenuScene>();
}
