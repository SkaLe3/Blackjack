#include "GameObjects/Card.h"
#include "World/Components/SpriteComponent.h"
#include "Renderer/Sprite.h"
#include "Core/AssetManager.h"

using namespace Core;


Card::Card()
{
	auto sprite = GetSpriteComponent();

	sprite->GetTransform().Scale = { 25, 35, 1 };
}

void Card::BeginPlay()
{
	Super::BeginPlay();
}

void Card::TurnOver()
{
	m_CardFace = static_cast<CardFace>(static_cast<byte>(m_CardFace) ^ 1);
	SelectFace();
}

void Card::AssignFrontFace(const String& faceName)
{
	m_FacesMapping[CardFace::Front] = faceName;
}

void Card::AssignBackFace(const String& backName)
{
	m_FacesMapping[CardFace::Back] = backName;
}

void Card::SetInitialState(CardFace initialFace)
{
	m_CardFace = initialFace;
	SelectFace();
}

void Card::SelectFace()
{	
	GetSpriteComponent()->SetRegion(m_FacesMapping[m_CardFace]);
}