#include "GameModes/GameplayGameMode.h"

#include "Scenes/MenuScene.h"
#include "GameObjects/Deck.h"
#include "GameObjects/Chip.h"  // For testing
#include "GameObjects/Card.h"
#include "GameObjects/UserPlayer.h"
#include "GameObjects/AIPlayer.h"
#include "GameObjects/Dealer.h"
#include "Components/DeckAnimationComponent.h"

#include <World/World/World.h>
#include <World/Entities/SpriteObject.h>
#include <World/Entities/CameraObject.h>
#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>
#include <Core/TimerManager.h>
#include <Core/Utils.h>

#include <Renderer/TextureAtlas.h>
#include <Renderer/Sprite.h>

#include <glm/ext/scalar_constants.hpp>
#include <random>
#include <SDL2/SDL.h>

using namespace Core;

void GameplayGameMode::OnEvent(Event& event)
{

	std::static_pointer_cast<UserPlayer>(m_Players[1])->OnEvent(event);

	if (event.Ev.type == SDL_KEYDOWN)
	{
		if (event.Ev.key.keysym.sym == SDLK_COMMA)
		{
			m_SelectedSkin = AssetManager::Get().Load<TextureAsset>("T_CardsAtlasFiltered")->TextureP;
			ChangeCardsSkin();
			BJ_LOG_INFO("Changed skin to White");
		}
		if (event.Ev.key.keysym.sym == SDLK_PERIOD)
		{
			m_SelectedSkin = AssetManager::Get().Load<TextureAsset>("T_CardsAtlasBlack")->TextureP;
			ChangeCardsSkin();
			BJ_LOG_INFO("Changed skin to Black");
		}
#ifdef BJ_DEBUG
		if (event.Ev.key.keysym.sym == SDLK_q)
		{
			if (m_Players[0]->IsAbleToTakeCard())
				m_Players[0]->TakeCard(m_Deck->PullCard());
		}
		if (event.Ev.key.keysym.sym == SDLK_w)
		{
			if (m_Players[1]->IsAbleToTakeCard())
				m_Players[1]->TakeCard(m_Deck->PullCard());
		}
		if (event.Ev.key.keysym.sym == SDLK_e)
		{
			if (m_Players[2]->IsAbleToTakeCard())
				m_Players[2]->TakeCard(m_Deck->PullCard());
		}
		if (event.Ev.key.keysym.sym == SDLK_r)
		{
			if (m_Dealer->IsAbleToTakeCard())
				m_Dealer->TakeCard(m_Deck->PullCard());
		}
		if (event.Ev.key.keysym.sym == SDLK_t)
		{
			if (m_Dealer->IsAbleToTakeCard())
				m_Dealer->PlaceCard(m_Deck->PullCard());
		}
#endif

	}
}

void GameplayGameMode::BeginPlay()
{
	Super::BeginPlay();
	SharedPtr<SoundBase> music = AssetManager::Get().Load<SoundAsset>("S_Music1")->SoundP;
	music->SetOneShot(false);
	AudioSystem::PlayMusic(music);
	AudioSystem::SetMusicVolume(0.2);
	SharedPtr<SoundBase> ambient = AssetManager::Get().Load<SoundAsset>("S_PokerAmbient")->SoundP;
	ambient->SetOneShot(false);
	AudioSystem::PlaySound(ambient, 0.2f);
	RestartGame();

}

void GameplayGameMode::Tick(float deltaTime)
{
	if (m_bShouldStartRound)
	{
		StartRound();
		return;
	}
	if (!m_bDeckReady)
	{
		return;
	}
	if (m_PlayerMakeTurn)
	{
		OnNewTurn();
		MakeTurn();
	}
	if (m_DealerMakeTurn)
	{
		m_DealerMakeTurn = false;
		m_Dealer->MakeTurn();
	}
	if (m_ContinueTurn)
	{
		m_ActivePlayers[m_PlayerTurn]->AllowTurn();
		m_ContinueTurn = false;
	}
	if (m_ShiftStage)
	{
		m_RoundStage = (ERoundStage)((byte)m_RoundStage + 1); // TODO: Make operator++()
		OnNewStage();
	}
	if ((ERoundStage)m_RoundStage == ERoundStage::Registration)
	{
		for (auto& player : m_Players)
		{
			bool registered = player->GetBalance() >= m_GameState->MinBet;
			if (registered)
			{
				player->GameState = m_GameState;
				player->ResetState();
				player->AllowToPlay(); // Sets all event callbacks
				m_ActivePlayers.push_back(player);
				m_GameState->NumberOfRegisteredPlayers++;
				BJ_LOG_INFO("%s Balance: %d", player->GetTag().c_str(), player->GetBalance());
			}
			else
			{
				//////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////
				//////////////////////////////////////
				//////////////////////////////////////
				//////////////////////////////////////

				//////////////////////////////////////
			}
			m_Dealer->GameState = m_GameState;
		}
		SubscribeForEvents();
		// Proceed to betting
		ShiftStage();

		// On this moment all players already subscribed for all events they need
	}
	else if ((ERoundStage)m_RoundStage == ERoundStage::Betting)
	{
		// Allows all players to place bets (if its their turn)
		m_GameState->OnBettingStageStarted.Invoke();
		if (WaitForBets())
		{
			ShiftStage();
			ResetTurn();
		}
	}
	else if ((ERoundStage)m_RoundStage == ERoundStage::DealingCards)
	{
		m_GameState->OnDealingcardsStageStarted.Invoke();
	}
	else if ((ERoundStage)m_RoundStage == ERoundStage::PlayerTurn)
	{
		m_GameState->OnPlayerTurnStageStarted.Invoke();
		if (WaitForTurns())
		{
			ShiftStage();
			ResetTurn();
		}
	}
	else if ((ERoundStage)m_RoundStage == ERoundStage::DealerReveal)
	{
		m_GameState->OnDealerRevealStageStarted.Invoke();
		if (WaitForReveal())
		{
			ShiftStage();
			ResetTurn();
		}
	}
	else if ((ERoundStage)m_RoundStage == ERoundStage::RoundResult)
	{
		m_GameState->OnRoundResultStageStarted.Invoke();
		if (WaitForFinished())
		{
			ShiftStage();
			ResetTurn();
		}
	}
	else if ((ERoundStage)m_RoundStage == ERoundStage::Restart)
	{
		m_GameState->OnRestartRoundStageStarted.Invoke();
	}

}

void GameplayGameMode::StartRound()
{
	// Remove all bindings
	m_GameState = MakeShared<BJGameState>();
	m_Deck = GetWorld()->SpawnGameObject<Deck>();
	m_Deck->GetTransform().Translation = { -66, 32, -100 };
	m_Deck->PopulateDeck(m_SelectedSkin);
	m_Deck->Shuffle();
	m_Deck->Animate({ 0, 70 }, -180.f, 0.f, 4.f, 1.f);
	m_Deck->GetAnimationComponent()->OnFinishShuffleAnim.Add(std::bind(&GameplayGameMode::OnDeckReady, this));
	m_CardsRef = m_Deck->GetCardsRef();
	m_RoundStage = ERoundStage::Registration;
	ResetTurn();

	m_bShouldStartRound = false;
}

void GameplayGameMode::EndRound()
{
	for (auto& player : m_Players)
	{
		player->ClearHand();
		player->ClearBet();
	}
	m_Dealer->ClearHand();
	m_Deck->Destroy();
	m_ActivePlayers.clear();
	m_CardsRef.clear();

	m_ShiftStage = false;
	m_bShouldStartRound = false;
	m_bDeckReady = false;
	m_PlayerMakeTurn = false;
	m_DealerMakeTurn = false;
	m_ContinueTurn = false;
	m_RoundStage = ERoundStage::None;	 
}


void GameplayGameMode::NextRound()
{
	EndRound();
	StartRound();
}

void GameplayGameMode::RestartGame()
{
	SharedPtr<CameraObject> camera = GetWorld()->SpawnGameObject<CameraObject>();

	auto cameraComp = camera->GetCameraComponent();
	cameraComp->GetCamera()->SetOrthoSize(100);

	SharedPtr<SpriteObject> table = GetWorld()->SpawnGameObject<SpriteObject>();
	table->GetSpriteComponent()->SetSprite(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_Table")->TextureP));
	table->GetTransform().Translation.z = -200;
	table->GetSpriteComponent()->GetTransform().Scale = { 178, 100, 1 };

	m_GameState = MakeShared<BJGameState>();

	m_Dealer = GetWorld()->SpawnGameObject<Dealer>();
	m_Dealer->SetLocation({ 0, 25 });
	m_Dealer->SetTag("Dealer");

	auto player = GetWorld()->SpawnGameObject<UserPlayer>();
	player->SetLocation({ 0, -41 });

	auto bot1 = GetWorld()->SpawnGameObject<AIPlayer>();
	bot1->SetLocation({ -70, -28 });
	bot1->GetTransform().Rotation.z = -glm::pi<float>() / 9;
	auto bot2 = GetWorld()->SpawnGameObject<AIPlayer>();
	bot2->SetLocation({ 70, -28 });
	bot2->GetTransform().Rotation.z = glm::pi<float>() / 9;

	m_Players.push_back(bot1);
	m_Players.push_back(player);
	m_Players.push_back(bot2);
	bot1->SetTag("Bot1");
	player->SetTag("User");
	bot2->SetTag("Bot2");
	bot1->SetBalance(m_GameState->InitialBalance);
	player->SetBalance(m_GameState->InitialBalance);
	bot2->SetBalance(m_GameState->InitialBalance);

	m_SelectedSkin = AssetManager::Get().Load<TextureAsset>("T_CardsAtlasFiltered")->TextureP;

	TimerManager::Get().StartTimer(3000, [this]() { m_bShouldStartRound = true; });
}

void GameplayGameMode::LeaveGame()
{
	// Scene changing handles all object destroying automatically
	AudioSystem::StopMusic();
	AudioSystem::StopAllSounds();
	World::OpenScene<MenuScene>();
}

void GameplayGameMode::OnDeckReady()
{
	m_bDeckReady = true;
}

void GameplayGameMode::OnBetPlaced()
{
	m_GameState->PlacedBetsCount++;
	ShiftTurn();
}

void GameplayGameMode::OnDealCards()
{
	float interval = m_GameState->CardsDealingInterval;
	int32 i = 0;
	/*
	 * Ensure that the interval between dealing cards to the same player exceeds the duration of the card dealing animation.
	 * In future iterations, implement a more comprehensive check for this condition.
	 * Currently, if there is only one player and the dealer in the game, the interval should be greater than 0.5 times the duration of the animation.
	 */
	for (auto& player : m_ActivePlayers)
	{
		// TODO: Make macro for binding, like for events
		TimerManager::Get().StartTimer(interval * i++, [=]() { DealCard(player); });
	}
	TimerManager::Get().StartTimer(interval * i++, [=]() { DealCard(m_Dealer); });
	i += 3;
	for (auto& player : m_ActivePlayers)
	{
		TimerManager::Get().StartTimer(interval * i++, [=]() { DealCard(player); });
	}
	TimerManager::Get().StartTimer(interval * i++, [=]() { DealCard(m_Dealer, false); });

	// Go to next stage
	TimerManager::Get().StartTimer(interval * i + 3000, [=]() { ShiftStage(); });
}

void GameplayGameMode::OnPlayersTurn()
{
	m_GameState->CurrentDealerHandValue = m_Dealer->GetHandValue();
	ShiftTurn();
}

void GameplayGameMode::OnDealerStartsReveal()
{
	m_ActivePlayers.erase(std::remove_if(m_ActivePlayers.begin(), m_ActivePlayers.end(),
										 [](const SharedPtr<Player>& ptr)
										 {
											 return ptr->HasFinishedGame();
										 }),
						  m_ActivePlayers.end());
	if (m_ActivePlayers.size() == 0)
		m_RoundStage = ERoundStage::Restart;

	TimerManager::Get().StartTimer(3000.f, [=]() { m_Dealer->StartReveal(); });

}

void GameplayGameMode::OnCheckResults()
{
	m_GameState->CurrentDealerHandValue = m_Dealer->GetHandValue();
	ShiftTurn();
}

void GameplayGameMode::OnPlayerHit(SharedPtr<Player> player)
{
	BJ_LOG_INFO("%s Hit", player->GetTag().c_str());
	if (player->IsAbleToTakeCard())
	{
		player->TakeCard(m_Deck->PullCard());
	}
	TimerManager::Get().StartTimer(2000.f, [this]() { m_ContinueTurn = true; });
}

void GameplayGameMode::OnPlayerStand(SharedPtr<Player> player)
{
	BJ_LOG_INFO("%s Stand", player->GetTag().c_str());
	EndTurnAction();
}

void GameplayGameMode::OnPlayerDoubleDown(SharedPtr<Player> player)
{
	BJ_LOG_INFO("%s DoubleDown", player->GetTag().c_str());
	if (player->IsAbleToTakeCard())
	{
		player->TakeCard(m_Deck->PullCard());
	}
	EndTurnAction();
}

void GameplayGameMode::OnPlayerCallBlackjack(SharedPtr<Player> player)
{
	BJ_LOG_INFO("%s Blackjack", player->GetTag().c_str());
	EndTurnAction();
	OnPlayerFinishedGame(player, EPlayerResult::BlackjackWin);
}

void GameplayGameMode::OnPlayerBust(SharedPtr<Player> player)
{
	BJ_LOG_INFO("%s Bust", player->GetTag().c_str());
	EndTurnAction();
	OnPlayerFinishedGame(player, EPlayerResult::Lose);

}

void GameplayGameMode::OnPlayerResultWin(SharedPtr<Player> player)
{
	BJ_LOG_INFO("%s Win by points", player->GetTag().c_str());
	EndTurnAction();
	OnPlayerFinishedGame(player, EPlayerResult::DefaultWin);
}

void GameplayGameMode::OnPlayerResultLose(SharedPtr<Player> player)
{
	BJ_LOG_INFO("%s Lose by points", player->GetTag().c_str());
	EndTurnAction();
	OnPlayerFinishedGame(player, EPlayerResult::Lose);
}

void GameplayGameMode::OnPlayerResultPush(SharedPtr<Player> player)
{
	BJ_LOG_INFO("%s Push", player->GetTag().c_str());
	EndTurnAction();
	OnPlayerFinishedGame(player, EPlayerResult::Push);
}

void GameplayGameMode::OnPlayerFinishedGame(SharedPtr<Player> player, EPlayerResult result)
{
	m_GameState->NumberOfFhinishedPlayers++;
	BJ_LOG_INFO("PLAYERS FINISHED: %d", (int32)m_GameState->NumberOfFhinishedPlayers);
	player->GameResult(result);
	float bet = player->GetBetValue();
	switch (result)
	{
	case EPlayerResult::BlackjackWin:
	{
		int32 prize = (int32)(bet * 1.5f);
		player->AddBalance(prize);
		BJ_LOG_INFO("%s Won %d", player->GetTag().c_str(), prize);
		break;
	}
	case EPlayerResult::DefaultWin:
	{
		int32 prize = (int32)bet;
		player->AddBalance(prize);
		BJ_LOG_INFO("%s Won %d", player->GetTag().c_str(), prize);
		break;
	}
	case EPlayerResult::Lose:
	{
		int32 prize = -(int32)bet;
		player->AddBalance(prize);
		BJ_LOG_INFO("%s Lost %d", player->GetTag().c_str(), prize);
		break;
	}
	case EPlayerResult::Push:
	{
		BJ_LOG_INFO("%s Win nothing", player->GetTag().c_str());
		break;
	}
	}
}

void GameplayGameMode::OnDealerRevealed()
{
	BJ_LOG_INFO("Dealer revealed");
	TimerManager::Get().StartTimer(4000.f, [this]() { m_DealerMakeTurn = true; });

}

void GameplayGameMode::OnDealerHit()
{
	BJ_LOG_INFO("Dealer Hit");
	if (m_Dealer->IsAbleToTakeCard())
	{
		m_Dealer->TakeCard(m_Deck->PullCard());
	}
	TimerManager::Get().StartTimer(2000.f, [this]() { m_DealerMakeTurn = true; });
}

void GameplayGameMode::OnDealerStand()
{
	BJ_LOG_INFO("Dealer Stand");
	OnDealerFinishedTurn();
}

void GameplayGameMode::OnDealerBust()
{
	BJ_LOG_INFO("Dealer Bust");
	OnDealerFinishedTurn();
}

void GameplayGameMode::OnDealerFinishedTurn()
{
	BJ_LOG_INFO("Dealer Finished Turn");
	TimerManager::Get().StartTimer(2000.f, [this]() { m_GameState->bDealerFinishedTurn = true; });
}

void GameplayGameMode::OnRestartRound()
{
	BJ_LOG_INFO("Restart Stage Started");
	for (auto& player : m_Players)
	{
		TimerManager::Get().StartTimer(2000.f, [=]() { player->AskForNextRound(); });	
	}
}

void GameplayGameMode::EndTurnAction()
{
	m_GameState->MadeTurnsCount++;
	ShiftTurn();
}

void GameplayGameMode::SubscribeForEvents()
{
	// Delegates for everyone
	// Gives turn to first player
	m_GameState->OnBettingStageStarted.Add([this]() { ShiftTurn(); });
	m_GameState->OnDealingcardsStageStarted.Add([this]() { OnDealCards(); });
	m_GameState->OnPlayerTurnStageStarted.Add([this]() { OnPlayersTurn(); });
	m_GameState->OnDealerRevealStageStarted.Add([this]() { OnDealerStartsReveal(); });
	m_GameState->OnRoundResultStageStarted.Add([this]() { OnCheckResults(); });
	m_GameState->OnRestartRoundStageStarted.Add([this]() { OnRestartRound(); });

	// Delegated for GameMode
	m_GameState->OnBetPlaced.Add([this]() { OnBetPlaced(); });
	m_GameState->OnPlayerHit.Add([this](SharedPtr<Player> player) { OnPlayerHit(player); });
	m_GameState->OnPlayerStand.Add([this](SharedPtr<Player> player) { OnPlayerStand(player); });
	m_GameState->OnPlayerDoubleDown.Add([this](SharedPtr<Player> player) { OnPlayerDoubleDown(player); });
	m_GameState->OnPlayerCallBlackjack.Add([this](SharedPtr<Player> player) { OnPlayerCallBlackjack(player); });
	m_GameState->OnPlayerBust.Add([this](SharedPtr<Player> player) { OnPlayerBust(player); });
	m_GameState->OnPlayerResultWin.Add([this](SharedPtr<Player> player) { OnPlayerResultWin(player); });
	m_GameState->OnPlayerResultLose.Add([this](SharedPtr<Player> player) { OnPlayerResultLose(player); });
	m_GameState->OnPlayerResultPush.Add([this](SharedPtr<Player> player) { OnPlayerResultPush(player); });

	m_GameState->OnDealerHit.Add([this]() { OnDealerHit(); });
	m_GameState->OnDealerStand.Add([this]() { OnDealerStand(); });
	m_GameState->OnDealerBust.Add([this]() { OnDealerBust(); });
	m_GameState->OnDealerRevealed.Add([this]() { OnDealerRevealed(); });


	m_GameState->OnNextRound.Add([this]() { NextRound(); });
	m_GameState->OnLeaveGame.Add([this]() { LeaveGame(); });

}

void GameplayGameMode::ShiftStage()
{
	m_ShiftStage = true;
}

void GameplayGameMode::OnNewStage()
{
	m_ShiftStage = false;
}

void GameplayGameMode::ShiftTurn()
{
	m_PlayerMakeTurn = true;
}

void GameplayGameMode::OnNewTurn()
{
	m_PlayerMakeTurn = false;
}

void GameplayGameMode::MakeTurn()
{
	if (m_PlayerTurn >= 0 && m_PlayerTurn < m_ActivePlayers.size())
	{
		m_ActivePlayers[m_PlayerTurn]->ForbidTurn();
	}
	m_PlayerTurn++;
	TimerManager::Get().StartTimer(2000.f, [this]()
								   {
									   if (m_PlayerTurn >= 0 && m_PlayerTurn < (int32)m_ActivePlayers.size())
									   {
										   m_ActivePlayers[m_PlayerTurn]->AllowTurn();
									   }
								   });
	BJ_LOG_INFO("PlayerTurn index: %d", m_PlayerTurn);
}

void GameplayGameMode::ResetTurn()
{
	m_PlayerTurn = -1;
}


bool GameplayGameMode::WaitForBets()
{
	return m_GameState->PlacedBetsCount == m_ActivePlayers.size();
}


bool GameplayGameMode::WaitForTurns()
{
	return m_GameState->MadeTurnsCount == m_ActivePlayers.size();
}

bool GameplayGameMode::WaitForReveal()
{
	return m_GameState->bDealerFinishedTurn;
}

bool GameplayGameMode::WaitForFinished()
{
	return m_GameState->NumberOfFhinishedPlayers == m_GameState->NumberOfRegisteredPlayers;
}

void GameplayGameMode::DealCard(SharedPtr<Person> person, bool bFronfaceUp /*= true*/)
{
	if (person->IsAbleToTakeCard())
	{
		if (bFronfaceUp)
		{
			person->TakeCard(m_Deck->PullCard());
		}
		else
		{
			person->PlaceCard(m_Deck->PullCard());
		}
	}
}

void GameplayGameMode::ChangeCardsSkin()
{
	for (const auto& card : m_CardsRef)
	{
		card->GetSpriteComponent()->GetAtlas()->ChangeTexture(m_SelectedSkin);
		card->GetSpriteComponent()->UpdateAtlas();
	}
}

