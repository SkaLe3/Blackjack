#pragma once
#include <World/Entities/PlayerController.h>


class MenuPlayerController : public Core::PlayerController
{
	DECLARE_SUPER(Core::PlayerController)
public:
	 void CreateMenuWidget();
};


