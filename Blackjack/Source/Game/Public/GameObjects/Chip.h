#pragma once

#include <World/Entities/SpriteObject.h>

class Chip : public Core::SpriteObject
{
	DECLARE_SUPER(Core::SpriteObject)
public:
	Chip();

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface
	
};