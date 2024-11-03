#include "GameObjects/Card.h"
#include "World/Components/SpriteComponent.h"
#include "Renderer/Sprite.h"
#include "Core/AssetManager.h"

using namespace Core;


Card::Card()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	auto sprite = GetSpriteComponent();
	sprite->SetupAttachment(GetBoxComponent());
	sprite->SetOwner(GetSelf());
	// Note: Texture Atlas (and Sprite) should be set by GameMode or by Deck during game start
	//		to use one Atlas instance across all cards.
	//		However Sprite cannot use flyweight pattern
	//		because it stores coordinates of texture source.
	//		But still all sprites will use the same Texture instance
	sprite->GetTransform().Scale = {25, 35, 1};

}

void Card::BeginPlay()
{
	Super::BeginPlay();
}

void Card::TurnOver()
{

	m_CardFace = static_cast<CardFace>(static_cast<byte>(m_CardFace) ^ 1);
	// TODO: flip actual face in sprite component
	/*
	* The XOR approach may offer a slight performance advantage by avoiding branching,
	* though it requires casting. However, performance should be tested to confirm.
	*/
	//m_CardFace = m_CardFace == CardFace::Front ? CardFace::Back : CardFace::Front; 
}
