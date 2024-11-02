#pragma once
#include "World/Entities/GameObject.h"



class Deck : public Core::GameObject
{
	DECLARE_SUPER(Core::GameObject)
public:

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface
};