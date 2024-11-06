#include "Components/ChipStackMovementComponent.h"

#include <Core/Utils.h>

using namespace Core;

void ChipStackMovementComponent::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (m_bMoving) UpdateMovement(deltaTime);
}

void ChipStackMovementComponent::StartMovement(float duration, const glm::vec2& start, const glm::vec2& target)
{
	if (auto chipStack = std::static_pointer_cast<ChipStack>(GetOwner().lock()))
	{
		m_ChipStack = chipStack;
		m_StartPosition = start;
		m_TargetPosition = target;
		m_Duration = duration;
		m_Elapsed = 0;
		m_bMoving = true;
	}
}

void ChipStackMovementComponent::UpdateMovement(float deltaTime)
{
	m_Elapsed += deltaTime;
	if (m_Elapsed < m_Duration)
	{
		float t = glm::clamp(m_Elapsed / m_Duration, 0.0f, 1.0f);
		float easedT = EaseInOutCubic(t);
		m_StackPos = Lerp(m_StartPosition, m_TargetPosition, easedT);
		m_ChipStack->SetLocation(m_StackPos);
	}
	else
	{
		m_ChipStack->SetLocation(m_TargetPosition);
		m_bMoving = false;
		m_Elapsed = 0;
		OnFinishedMovement.Invoke();
	}
}
