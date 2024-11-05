#pragma once
#include <World/Components/GameComponent.h>

#include "GameObjects/Card.h"

DECLARE_DELEGATE_NO_PARAMS(CardFinishMoveAnimationDelegate)

class CardAnimationComponent : public Core::GameComponent
{
	DECLARE_SUPER(Core::GameComponent)
public:
	//~ Begin Object Interface
	virtual void Tick(float deltaTime) override;
	//~ End Object Interface

	void StartFlipAnimation(float duration, byte axis = 0); // 0: x, 1: y
	void StartTransformAnimation(float duration, const glm::vec2& start, const glm::vec2& target, float startRot = 0, float targetRot = 0, bool clockwise = false);

private:
	void UpdateFlip(float deltaTime);
	void UpdateTransform(float deltaTime);


public:
	CardFinishMoveAnimationDelegate OnFinishMoveAnim;

private:
	SharedPtr<Card> m_Card;
	glm::vec2 m_StartPosition, m_TargetPosition;
	glm::vec2 m_CardTranslation;
	glm::vec3 m_CardScale;
	float m_StartRotation, m_TargetRotation = 0.0f;
	float m_CardRotation = 0.0f;
	float m_FlipDuration = 0.0f;
	float m_TransformDuration = 0.0f;
	float m_FlipElapsed = 0.0f;
	float m_TransformElapsed = 0.0f;
	uint8_t m_flipAxis = 0;
	bool m_bFlipFlag = false;
	bool m_bAnimatingFlip = false;
	bool m_bAnimatingTransform = false;
	bool m_bClockwise = false;

};