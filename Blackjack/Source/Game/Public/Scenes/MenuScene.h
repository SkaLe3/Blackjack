#pragma once
#include "World/World/World.h"
#include "Core/Event.h"

class MenuScene : public Core::World
{
public:
	MenuScene() = default;

	//~ Begin World Interface
	virtual void BeginPlay() override;
	virtual void OnEvent(Core::Event& event) override;
	//~ End World Interface
};