#include "GameModes/GameplayGameMode.h"
#include "World/Entities/GameObject.h"
#include "World/World/World.h"
#include "Core/AssetManager.h"
#include "Renderer/Sprite.h"
#include "World/Entities/CameraObject.h"
#include "Assets/CardTextureAtlas.h"

#include "Scenes/MenuScene.h"


#include "GameObjects/Card.h"

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


	SharedPtr<TextureAtlas> atlas = MakeShared<CardTextureAtlas>();


	SharedPtr<Card> card = GetWorld()->SpawnGameObject<Card>();
	auto cardSprite = card->GetSpriteComponent();
	cardSprite->SetAtlas(atlas);
	cardSprite->SetRegion("2_spades");

	SharedPtr<Card> card2 = GetWorld()->SpawnGameObject<Card>();
	auto cardSprite2 = card2->GetSpriteComponent();
	cardSprite2->SetAtlas(atlas);
	cardSprite2->SetRegion("back");

	SharedPtr<Card> card3 = GetWorld()->SpawnGameObject<Card>();
	auto cardSprite3 = card3->GetSpriteComponent();
	cardSprite3->SetAtlas(atlas);
	cardSprite3->SetRegion("J_diamonds");

	card->SetLocation({ -30, 0 });
	card2->SetLocation({ 0, 0 });
	card3->GetTransform().Translation.z = -1;
	card3->SetLocation({ 30, 0 });
	//cardSprite2->GetTransform().Translation.x = 40;	
	//card->GetTransform().Translation.x = 40;
	//card->GetTransform().Rotation.z = 1.5708;
}

void GameplayGameMode::LeaveGame()
{
	World::OpenScene<MenuScene>();
}
