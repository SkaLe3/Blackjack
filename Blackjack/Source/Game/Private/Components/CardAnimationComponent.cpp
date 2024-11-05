#include "Components/CardAnimationComponent.h"

#include <Core/Utils.h>


using namespace Core;


void CardAnimationComponent::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (m_bAnimatingFlip) UpdateFlip(deltaTime);
	if (m_bAnimatingTransform) UpdateTransform(deltaTime);
	if (!m_bAnimatingFlip && !m_bAnimatingTransform) m_Card = nullptr;

}

void CardAnimationComponent::StartFlipAnimation(float duration, byte axis)
{
	if (auto cardOwner = std::static_pointer_cast<Card>(GetOwner().lock()))
	{
		m_Card = cardOwner;
		m_FlipDuration = duration;
		m_CardScale = m_Card->GetSpriteComponent()->GetTransform().Scale;
		m_flipAxis = axis;
		m_bFlipFlag = false;
		m_bAnimatingFlip = true;
		m_FlipElapsed = 0;
	}
}


void CardAnimationComponent::StartTransformAnimation(float duration, const glm::vec2& start, const glm::vec2& target, float startRot /*= 0*/, float targetRot /*= 0*/, bool clockwise /*= false*/)
{
	if (auto cardOwner = std::static_pointer_cast<Card>(GetOwner().lock()))
	{
		m_Card = cardOwner;
		m_StartPosition = start;
		m_TargetPosition = target;
		m_StartRotation = glm::radians(startRot);
		targetRot = clockwise ? 0 - targetRot : targetRot;
		m_TargetRotation = glm::radians(targetRot);
		m_TransformDuration = duration;
		m_bAnimatingTransform = true;
		m_TransformElapsed = 0;
	}
}

void CardAnimationComponent::UpdateFlip(float deltaTime)
{
	m_FlipElapsed += deltaTime;
	float halfDuration = m_FlipDuration * 0.5f;

	if (m_FlipElapsed < m_FlipDuration)
	{
		float progress = m_FlipElapsed / halfDuration;
		float scale = glm::abs(glm::cos(progress * glm::half_pi<float>()));
		m_Card->GetSpriteComponent()->GetTransform().Scale[m_flipAxis] = scale * m_CardScale[m_flipAxis];

		if (m_FlipElapsed >= halfDuration && !m_bFlipFlag)
		{
			m_bFlipFlag = true;
			m_Card->Flip();
		}
	}
	else
	{
		m_Card->GetSpriteComponent()->GetTransform().Scale[m_flipAxis] = m_CardScale[m_flipAxis];
		m_bAnimatingFlip = false;
		m_FlipElapsed = 0;
	}
}

void CardAnimationComponent::UpdateTransform(float deltaTime)
{
	m_TransformElapsed += deltaTime;
	if (m_TransformElapsed < m_TransformDuration)
	{
		float t = glm::clamp(m_TransformElapsed / m_TransformDuration, 0.0f, 1.0f);
		float easedT = EaseInOutCubic(t);
		m_CardTranslation = Lerp(m_StartPosition, m_TargetPosition, easedT);

		m_CardRotation = Lerp(m_StartRotation, m_TargetRotation, easedT);

		m_Card->SetLocation(m_CardTranslation);
		m_Card->GetTransform().Rotation.z = m_CardRotation;
	}
	else
	{
		m_Card->SetLocation(m_TargetPosition);
		m_Card->GetTransform().Rotation.z = m_TargetRotation;
		m_bAnimatingTransform = false;
		m_TransformElapsed = 0;
		OnFinishMoveAnim.Invoke();
	}
}
