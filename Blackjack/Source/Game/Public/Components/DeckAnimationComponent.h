#pragma once
#include "World/Components/GameComponent.h"

#include "GameObjects/Deck.h"

#include <Sound/Sound.h>

DECLARE_DELEGATE_NO_PARAMS(DeckFinishShuffleAnimationDelegate)

class DeckAnimationComponent : public Core::GameComponent
{
	DECLARE_SUPER(Core::GameComponent)
public:
	DeckAnimationComponent();
	//~ Begin Object Interface
	virtual void Tick(float deltaTime) override;
	//~ End Object Interface

	void StartShuffleAnimation(const glm::vec2& startPos, float sourceRot, float targetRot, float durationShuffle, float durationCard);
	void UpdateShuffle(float deltaTime);


public:
	DeckFinishShuffleAnimationDelegate OnFinishShuffleAnim;

private:
	SharedPtr<Deck> m_Deck;
	glm::vec2 m_StartPos;
	float m_SourceRotation;
	float m_TargetRotation;
	float m_DurationShuffle;
	float m_DurationCard;
	float m_Elapsed = 0.f;
	bool m_bAnimating = false;

	int32 m_LastAnimatedIndex = 0;

	std::vector<glm::vec2> m_Positions;
	SharedPtr<Core::SoundBase> m_CardSound;

};