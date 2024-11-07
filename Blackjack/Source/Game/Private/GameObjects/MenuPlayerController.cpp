#include "GameObjects/MenuPlayerController.h"

#include "Widgets/MenuWidgetLayout.h"


using namespace Core;

void MenuPlayerController::CreateMenuWidget()
{
	if (SharedPtr<MenuWidgetLayout> myWidget = CreateWidgetLayout<MenuWidgetLayout>("Menu"))
	{
		myWidget->Init();
		myWidget->AddToViewport(1);
	}
}
