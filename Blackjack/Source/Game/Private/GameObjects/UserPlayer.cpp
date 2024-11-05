#include "GameObjects/UserPlayer.h"

#include "GameObjects/Chip.h"

using namespace Core;

void UserPlayer::BeginPlay()
{
	Super::BeginPlay();
}


void UserPlayer::OnEvent(Event& event)
{
	if (event.Ev.type == SDL_KEYDOWN)
	{
		if (m_State->AllowedToBet && IsMyTurn())
		{

			if (event.Ev.key.keysym.sym == SDLK_1)
			{
				PlaceChip(EChipType::White);
			}
			if (event.Ev.key.keysym.sym == SDLK_2)
			{
				PlaceChip(EChipType::Red);
			}
			if (event.Ev.key.keysym.sym == SDLK_3)
			{
				PlaceChip(EChipType::Blue);
			}
			if (event.Ev.key.keysym.sym == SDLK_4)
			{
				PlaceChip(EChipType::Gray);
			}
			if (event.Ev.key.keysym.sym == SDLK_5)
			{
				PlaceChip(EChipType::Green);
			}
			if (event.Ev.key.keysym.sym == SDLK_6)
			{
				PlaceChip(EChipType::Orange);
			}
			if (event.Ev.key.keysym.sym == SDLK_MINUS)
			{
				TakeLastChip();
			}
			if (event.Ev.key.keysym.sym == SDLK_EQUALS)
			{
				ConfirmBet();
			}
		}
	}



	// TODO: Move to widget
	static EChipType chipType;
}
