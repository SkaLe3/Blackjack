#include "GameModes/GameplayGameMode.h"

#include "Scenes/MenuScene.h"
#include "GameObjects/Deck.h"
#include "GameObjects/Chip.h"  // For testing
#include "GameObjects/UserPlayer.h"
#include "GameObjects/AIPlayer.h"
#include "GameObjects/Dealer.h"

#include <World/World/World.h>
#include <World/Entities/SpriteObject.h>
#include <World/Entities/CameraObject.h>
#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>

#include "Renderer/Sprite.h"

#include <glm/ext/scalar_constants.hpp>
#include <random>

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
	if (m_ShiftStage)
	{
		m_RoundStage = (ERoundStage)((byte)m_RoundStage + 1); // TODO: Make operator++()
		m_ShiftStage = false;
	}
	if ((ERoundStage)m_RoundStage == ERoundStage::Betting)
	{
		if (!m_GameState.BettingStarted)
		{
			m_GameState.BettingStarted = true;
		}
		m_ShiftStage = WaitForBets();
	}
}

void GameplayGameMode::StartRound()
{
	m_Deck = GetWorld()->SpawnGameObject<Deck>();
	m_Deck->GetTransform().Translation = { -66, 32, -100 };
	m_Deck->PopulateDeck();
	m_Deck->Shuffle();

	m_RoundStage = ERoundStage::Betting;

	m_PStates[0]->AllowedToBet = true;


}

void GameplayGameMode::EndRound()
{
	for (auto& player : m_Players)
	{
		player->ClearHand();
	}

	m_Deck->Destroy();
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

	m_PStates.emplace_back(MakeShared<PlayerState>());
	m_PStates.emplace_back(MakeShared<PlayerState>());
	m_PStates.emplace_back(MakeShared<PlayerState>());
	m_Players[0]->SetState(m_PStates[0]);
	m_Players[1]->SetState(m_PStates[1]);
	m_Players[2]->SetState(m_PStates[2]);

	StartRound();
}

void GameplayGameMode::LeaveGame()
{
	// Scene changing handles all object destroying automatically
	AudioSystem::StopMusic();
	AudioSystem::StopAllSounds();
	World::OpenScene<MenuScene>();
}

void GameplayGameMode::BetPlacedEvent()
{
	m_GameState.PlacedBetsCount++;
	m_PStates[m_PlayerTurn]->AllowedToBet = false;
	if (m_PlayerTurn < m_GameState.NumberOfPlayers -1)
		m_PStates[m_PlayerTurn+1]->AllowedToBet = true;
	m_PlayerTurn++;
}

void GameplayGameMode::StartBetting()
{

}

bool GameplayGameMode::WaitForBets()
{
	return m_GameState.PlacedBetsCount == m_GameState.NumberOfPlayers;
}

