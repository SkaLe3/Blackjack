#include "GameModes/GameplayGameMode.h"
#include "World/Entities/GameObject.h"
#include "World/World/World.h"
#include "Core/AssetManager.h"
#include "Renderer/Sprite.h"
#include "World/Entities/CameraObject.h"
#include "Assets/CardTextureAtlas.h"

#include "Scenes/MenuScene.h"

#include "GameObjects/Deck.h"

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


	auto deck = GetWorld()->SpawnGameObject<Deck>();
	deck->PopulateDeck();
	

}

void GameplayGameMode::LeaveGame()
{
	World::OpenScene<MenuScene>();
}
