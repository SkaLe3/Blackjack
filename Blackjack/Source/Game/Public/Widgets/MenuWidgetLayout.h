#pragma once
#include <UISystem/WidgetLayout.h>

#include <UISystem/Widgets/ImageWidget.h>
#include <UISystem/Widgets/ButtonWidget.h>
#include "Widgets/MuteButtonWidget.h"



class MenuWidgetLayout : public Core::WidgetLayout
{
public:	
	MenuWidgetLayout(const String& inName) : Core::WidgetLayout(inName) {}

	virtual void Init() override;



public:
	WeakPtr<Core::ImageWidget> Background;
	WeakPtr<Core::ButtonWidget> StartButton;
	WeakPtr<Core::ButtonWidget> LeaveButton;
	WeakPtr<Core::ButtonWidget> AddSkinButton;

	WeakPtr<Core::ToggleButtonWidget> MuteMusicButton;
	WeakPtr<Core::ToggleButtonWidget> MuteSoundButton;



};
