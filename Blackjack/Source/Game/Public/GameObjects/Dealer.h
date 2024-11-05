#pragma once
#include "GameObjects/Person.h"

class Dealer : public Person
{
	DECLARE_SUPER(Person)
public:
	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

};