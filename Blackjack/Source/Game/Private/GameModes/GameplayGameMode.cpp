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

	if (event.Ev.type == SDL_KEYDOWN)
	{
		if (event.Ev.key.keysym.sym == SDLK_EQUALS)
		{

			int number = distr(gen);
			m_Player->PlaceChip(chipvec[number]);
		}
		if (event.Ev.key.keysym.sym == SDLK_MINUS)
		{
			m_Player->TakeLastChip();
		}

		if (event.Ev.key.keysym.sym == SDLK_2)
		{

			int number = distr(gen);
			m_Bot1->PlaceChip(chipvec[number]);
		}
		if (event.Ev.key.keysym.sym == SDLK_1)
		{
			m_Bot1->TakeLastChip();
		}
		if (event.Ev.key.keysym.sym == SDLK_4)
		{

			int number = distr(gen);
			m_Bot2->PlaceChip(chipvec[number]);
		}
		if (event.Ev.key.keysym.sym == SDLK_3)
		{
			m_Bot2->TakeLastChip();
		}

		if (event.Ev.key.keysym.sym == SDLK_q)
		{
			if (m_Bot1->IsAbleToTakeCard())
				m_Bot1->TakeCard(m_Deck->PullCard());
		}
		if (event.Ev.key.keysym.sym == SDLK_w)
		{
			if (m_Player->IsAbleToTakeCard())
				m_Player->TakeCard(m_Deck->PullCard());
		}
		if (event.Ev.key.keysym.sym == SDLK_e)
		{
			if (m_Bot2->IsAbleToTakeCard())
				m_Bot2->TakeCard(m_Deck->PullCard());
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

void GameplayGameMode::StartRound()
{
	m_Deck = GetWorld()->SpawnGameObject<Deck>();
	m_Deck->GetTransform().Translation = { -66, 32, -100 };
	m_Deck->PopulateDeck();
}

void GameplayGameMode::EndRound()
{
	m_Player->ClearHand();
	m_Deck->Destroy();
}

void GameplayGameMode::NextRound()
{
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
	m_Dealer->SetLocation({0, 25});

	m_Player = GetWorld()->SpawnGameObject<UserPlayer>();
	m_Player->SetLocation({ 0, -41 });

	m_Bot1 = GetWorld()->SpawnGameObject<AIPlayer>();
	m_Bot1->SetLocation({ -70, -28 });
	m_Bot1->GetTransform().Rotation.z = -glm::pi<float>() / 9;
	m_Bot2 = GetWorld()->SpawnGameObject<AIPlayer>();
	m_Bot2->SetLocation({ 70, -28 });
	m_Bot2->GetTransform().Rotation.z = glm::pi<float>() / 9;
	StartRound();
}

void GameplayGameMode::LeaveGame()
{
	// Scene changing handles all object destroying automatically
	AudioSystem::StopMusic();
	AudioSystem::StopAllSounds();
	World::OpenScene<MenuScene>();
}


