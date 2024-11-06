#pragma once
#include <World/Components/GameComponent.h>

#include "GameObjects/ChipStack.h"

DECLARE_DELEGATE_NO_PARAMS(ChipStackFinishMovementDelegate)

class ChipStackMovementComponent : public Core::GameComponent
{
	DECLARE_SUPER(Core::GameComponent)
public:
	//~ Begin Object Interface
	virtual void Tick(float deltaTime) override;
	//~ End Object Interface

	void StartMovement(float duration, const glm::vec2& start, const glm::vec2& target);

private:
	void UpdateMovement(float deltaTime);

public:
	ChipStackFinishMovementDelegate OnFinishedMovement;

private:
	SharedPtr<ChipStack> m_ChipStack;
	glm::vec2 m_StartPosition, m_TargetPosition;
	glm::vec2 m_StackPos;
	float m_Duration;
	float m_Elapsed;
	bool m_bMoving;
};