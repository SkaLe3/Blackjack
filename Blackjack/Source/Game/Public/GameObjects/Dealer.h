#pragma once
#include "GameObjects/Person.h"

#include <Sound/Sound.h>

class Dealer : public Person
{
	DECLARE_SUPER(Person)
public:
	Dealer();
	//~ Begin Object Interface
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	//~ End Object Interface

	//~ Begin Person Interface
	virtual void Hit();
	virtual void Stand();
	virtual void Bust();
	//~ End Person Interface	

	void StartReveal();
	void MakeTurn();

private:
	bool m_bRevealed = false;

	SharedPtr<Core::SoundBase> m_ConfirmSound;
};