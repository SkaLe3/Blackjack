#include "GameModes/GameplayGameMode.h"

#include "Scenes/MenuScene.h"
#include "GameObjects/Deck.h"
#include "GameObjects/Chip.h"  // For testing
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

#include "Renderer/Sprite.h"

#include <glm/ext/scalar_constants.hpp>
#include <random>
#include <SDL2/SDL.h>

using namespace Core;

void GameplayGameMode::OnEvent(Event& event)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<>	distr(0, 5);
	static std::vector<EChipType> chipvec = { EChipType::White,
	EChipType::Red, EChipType::Blue, EChipType::Gray,
	EChipType::Green, EChipType::Orange };

	std::static_pointer_cast<UserPlayer>(m_Players[1])->OnEvent(event);

	if (event.Ev.type == SDL_KEYDOWN)
	{
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
	RestartGame();
	SharedPtr<SoundBase> music = AssetManager::Get().Load<SoundAsset>("S_Music1")->SoundP;
	AudioSystem::PlayMusic(music);
	AudioSystem::SetMusicVolume(0.2);
	SharedPtr<SoundBase> ambient = AssetManager::Get().Load<SoundAsset>("S_PokerAmbient")->SoundP;
	ambient->SetOneShot(false);
	AudioSystem::PlaySound(ambient, 0.2f);

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
				player->AllowToPlay(); // Sets all event callbacks
				m_ActivePlayers.push_back(player);
				m_GameState->NumberOfPlayers++;
				BJ_LOG_INFO("%s Balance: %d", player->GetTag().c_str(), player->GetBalance());
			}
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
}

void GameplayGameMode::StartRound()
{
	// Remove all bindings
	m_GameState = MakeShared<BJGameState>();

	m_Deck = GetWorld()->SpawnGameObject<Deck>();
	m_Deck->GetTransform().Translation = { -66, 32, -100 };
	m_Deck->PopulateDeck();
	m_Deck->Shuffle();
	m_Deck->Animate({ 0, 70 }, -180.f, 0.f, 4.f, 1.f);
	m_Deck->GetAnimationComponent()->OnFinishShuffleAnim.Add(std::bind(&GameplayGameMode::OnDeckReady, this));

	m_RoundStage = ERoundStage::Registration;
	ResetTurn();

	m_bShouldStartRound = false;
}

void GameplayGameMode::EndRound()
{
	for (auto& player : m_Players)
	{
		player->ClearHand();
	}

	m_Deck->Destroy();
	// TODO: Start the round again, but move it to be called after player confirmation to play new round
}

void GameplayGameMode::RoundResult()
{
	// Win or lose state
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

void GameplayGameMode::OnPlayerHit(SharedPtr<Player> player)
{
	BJ_LOG_INFO("%s Hit", player->GetTag().c_str());
	if (player->IsAbleToTakeCard())
	{
		player->TakeCard(m_Deck->PullCard());
	}
	EndTurnAction();
}

void GameplayGameMode::OnPlayerStand(SharedPtr<Player> player)
{
	BJ_LOG_INFO("%s Stand", player->GetTag().c_str());
	EndTurnAction();
}

void GameplayGameMode::OnPlayerDoubleDown(SharedPtr<Player> player)
{
	BJ_LOG_INFO("%s DoubleDown", player->GetTag().c_str());
	EndTurnAction();
}

void GameplayGameMode::OnPlayerCallBlackjack(SharedPtr<Player> player)
{
	BJ_LOG_INFO("%s Blackjack", player->GetTag().c_str());
	EndTurnAction();
	OnPlayerFinishedGame(player, EPlayerResult::BlackjackWin);
}

void GameplayGameMode::OnPlayerFinishedGame(SharedPtr<Player> player, EPlayerResult result)	
{
	 m_ActivePlayers.erase(std::remove(m_ActivePlayers.begin(), m_ActivePlayers.end(), player), m_ActivePlayers.end());
	 player->GameResult(result);
	 // Handle balance
}

void GameplayGameMode::EndTurnAction()
{
	m_GameState->MadeTurnsCount++;
	ShiftTurn();
}

void GameplayGameMode::SubscribeForEvents()
{
	// Gives turn to first player
	m_GameState->OnBettingStageStarted.Add([this]() { ShiftTurn(); });
	m_GameState->OnDealingcardsStageStarted.Add([this]() { OnDealCards(); });
	m_GameState->OnPlayerTurnStageStarted.Add([this]() { ShiftTurn(); });
	m_GameState->OnBetPlaced.Add([this]() { OnBetPlaced(); });
	m_GameState->OnPlayerHit.Add([this](SharedPtr<Player> player) { OnPlayerHit(player); });
	m_GameState->OnPlayerStand.Add([this](SharedPtr<Player> player) { OnPlayerStand(player); });
	m_GameState->OnPlayerDoubleDown.Add([this](SharedPtr<Player> player) { OnPlayerDoubleDown(player); });
	m_GameState->OnPlayerCallBlackjack.Add([this](SharedPtr<Player> player) { OnPlayerCallBlackjack(player); });

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
	if (m_PlayerTurn >= 0 && m_PlayerTurn < m_ActivePlayers.size())
	{
		m_ActivePlayers[m_PlayerTurn]->ForbidTurn();
	}
	if (m_PlayerTurn + 1 < (int32)m_ActivePlayers.size())
	{
		m_ActivePlayers[m_PlayerTurn + 1]->AllowTurn();
		m_PlayerTurn++;
	}

}

void GameplayGameMode::ResetTurn()
{
	m_PlayerTurn = -1;
}

void GameplayGameMode::StartBetting()
{

}

bool GameplayGameMode::WaitForBets()
{
	return m_GameState->PlacedBetsCount == m_ActivePlayers.size();
}


bool GameplayGameMode::WaitForTurns()
{
	return m_GameState->MadeTurnsCount == m_ActivePlayers.size();
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

