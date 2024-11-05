#include "GameObjects/Card.h"
#include <World/Components/SpriteComponent.h>
#include <Renderer/Sprite.h>
#include <Core/AssetManager.h>

#include "Components/CardAnimationComponent.h"

using namespace Core;


Card::Card()
{
	m_AnimComp = CreateComponent<CardAnimationComponent>();

	auto sprite = GetSpriteComponent();
	sprite->GetTransform().Scale = { 17.5, 24.5, 1 };
}

void Card::BeginPlay()
{
	Super::BeginPlay();
	GetAnimationComponent()->SetOwner(GetSelf());
}

void Card::Destroy()
{
	Super::Destroy();
	GetAnimationComponent()->Destroy();
}


int32 Card::GetValue()
{
	 return (int32)(byte)m_Rank;
}

ECardRank Card::GetRank()
{
	return m_Rank;
}

void Card::TurnOver(float duration, byte axis /*= 0*/)
{
	GetAnimationComponent()->StartFlipAnimation(duration, axis);
}

void Card::Flip()
{
	m_CardFace = static_cast<ECardFace>(static_cast<byte>(m_CardFace) ^ 1);
	SelectFace();
	GetSpriteComponent()->GetTransform().Rotation.z += glm::radians(180.0f);
	glm::mat4 mmm = GetSpriteComponent()->GetTransformMatrix();
}

void Card::Move(float duration, const glm::vec2& start, const glm::vec2& target, float startRot /*= 0*/, float targetRot /*= 0*/, bool clockwise /*= false*/)
{
	GetAnimationComponent()->StartTransformAnimation(duration, start, target, startRot, targetRot, clockwise);
}

void Card::AssignFrontFace(const String& faceName)
{
	m_FacesMapping[ECardFace::Front] = faceName;
}

void Card::AssignBackFace(const String& backName)
{
	m_FacesMapping[ECardFace::Back] = backName;
}

void Card::AssignRank(ECardRank rank)
{
	m_Rank = rank;
}

void Card::SetInitialState(ECardFace initialFace)
{
	m_CardFace = initialFace;
	SelectFace();
}

SharedPtr<CardAnimationComponent> Card::GetAnimationComponent()
{
	return m_AnimComp.lock();
}

void Card::SelectFace()
{	
	GetSpriteComponent()->SetRegion(m_FacesMapping[m_CardFace]);
}
