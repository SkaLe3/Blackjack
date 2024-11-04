#include "GameObjects/Card.h"
#include "World/Components/SpriteComponent.h"
#include "Renderer/Sprite.h"
#include "Core/AssetManager.h"

using namespace Core;


Card::Card()
{
	auto sprite = GetSpriteComponent();

	sprite->GetTransform().Scale = { 20, 28, 1 };
}

void Card::BeginPlay()
{
	Super::BeginPlay();
}

void Card::TurnOver()
{
	m_CardFace = static_cast<ECardFace>(static_cast<byte>(m_CardFace) ^ 1);
	SelectFace();
	glm::mat4 mmm = GetSpriteComponent()->GetTransformMatrix();
}

void Card::AssignFrontFace(const String& faceName)
{
	m_FacesMapping[ECardFace::Front] = faceName;
}

void Card::AssignBackFace(const String& backName)
{
	m_FacesMapping[ECardFace::Back] = backName;
}

void Card::SetInitialState(ECardFace initialFace)
{
	m_CardFace = initialFace;
	SelectFace();
}

void Card::SelectFace()
{	
	GetSpriteComponent()->SetRegion(m_FacesMapping[m_CardFace]);
}
