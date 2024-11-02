#pragma once
#include "World/World/World.h"

class GameplayScene : public Core::World
{
public:
	GameplayScene() = default;

	//~ Begin World Interface
	virtual void BeginPlay() override;
	virtual void OnEvent(Core::Event& event) override;
	//~ End World Interface
};