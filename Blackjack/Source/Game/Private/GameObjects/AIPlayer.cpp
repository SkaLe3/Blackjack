#include "GameObjects/AIPlayer.h"

#include <SDL2/SDL.h>


void AIPlayer::Tick(float deltaTime)
{
	if (auto state = m_State.lock())
	{
		if (state->AllowedToBet)
		{
			PlaceChip(EChipType::Blue);
			ConfirmBet();

		}
	}
}

void AIPlayer::PlaceBet()
{

}
