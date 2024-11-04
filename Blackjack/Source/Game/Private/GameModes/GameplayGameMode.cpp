#include "GameModes/GameplayGameMode.h"

#include "Scenes/MenuScene.h"
#include "GameObjects/Deck.h"
#include "GameObjects/Chip.h"  // For testing
#include "GameObjects/Player.h"

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
			m_Player->TakeCard(m_Deck->PullCard());
		}


	}
}

void GameplayGameMode::BeginPlay()
{		
	Super::BeginPlay();
	RestartGame();
}

void GameplayGameMode::RestartGame()
{
	SharedPtr<SoundBase> music = AssetManager::Get().Load<SoundAsset>("S_Music1")->SoundP;
	AudioSystem::PlayMusic(music);
	AudioSystem::SetMusicVolume(0.2);

	SharedPtr<CameraObject> camera = GetWorld()->SpawnGameObject<CameraObject>();

	auto cameraComp = camera->GetCameraComponent();
	cameraComp->GetCamera()->SetOrthoSize(100);

	SharedPtr<SpriteObject> table = GetWorld()->SpawnGameObject<SpriteObject>();
	table->GetSpriteComponent()->SetSprite(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_Table")->TextureP));
	table->GetTransform().Translation.z = -200;
	table->GetSpriteComponent()->GetTransform().Scale = { 177, 100, 1 };

	m_Deck = GetWorld()->SpawnGameObject<Deck>();
	m_Deck->PopulateDeck();
	m_Deck->GetTransform().Translation = { -60, 26, -100 };

	m_Player = GetWorld()->SpawnGameObject<Player>();
	m_Player->SetLocation({0, -30});

	m_Bot1 = GetWorld()->SpawnGameObject<Player>();
	m_Bot1->SetLocation({-60, -20});
	m_Bot1->GetTransform().Rotation.z = glm::pi<float>() / 6;
	m_Bot2 = GetWorld()->SpawnGameObject<Player>();
	m_Bot2->SetLocation({60, -20});
	m_Bot2->GetTransform().Rotation.z = - glm::pi<float>() / 6;
	




}

void GameplayGameMode::LeaveGame()
{
	AudioSystem::StopMusic();
	AudioSystem::StopAllSounds();
	World::OpenScene<MenuScene>();
}


