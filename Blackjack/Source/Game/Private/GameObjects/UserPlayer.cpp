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

			if (event.Ev.key.keysym.sym == SDLK_EQUALS)
			{
				PlaceChip(EChipType::Red);
			}
			if (event.Ev.key.keysym.sym == SDLK_MINUS)
			{
				TakeLastChip();
			}
			if (event.Ev.key.keysym.sym == SDLK_0)
			{
				ConfirmBet();
			}
		}
	}



	// TODO: Move to widget
	static EChipType chipType;
}
