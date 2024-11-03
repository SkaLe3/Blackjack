#pragma once

#include "World/Entities/GameObject.h"

enum class CardFace : byte
{
	Front = 0,
	Back = 1
};

class Core::SpriteComponent;

class Card : public Core::GameObject
{
	DECLARE_SUPER(Core::GameObject)
public:
	Card();

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	SharedPtr<Core::SpriteComponent> GetSpriteComponent() { return m_SpriteComponent.lock(); }

	void TurnOver();

private:
	WeakPtr<Core::SpriteComponent> m_SpriteComponent;

	CardFace m_CardFace;


};

