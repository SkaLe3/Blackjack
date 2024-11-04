#include "GameModes/GameplayGameMode.h"

#include "Scenes/MenuScene.h"
#include "GameObjects/Deck.h"
#include "GameObjects/Chip.h"
#include "GameObjects/ChipStack.h"

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
	if (event.Ev.type == SDL_KEYDOWN)
	{
		if (event.Ev.key.keysym.sym == SDLK_EQUALS)
		{
			static std::random_device rd;
			static std::mt19937 gen(rd());
			static std::uniform_int_distribution<>	distr(0, 5);
			static std::vector<EChipType> chipvec = {EChipType::White,
			EChipType::Red, EChipType::Blue, EChipType::Gray,
			EChipType::Green, EChipType::Orange};
			int number = distr(gen);
			m_ChipStack->AddChip(chipvec[number]);
		}
		if (event.Ev.key.keysym.sym == SDLK_MINUS)
		{
			m_ChipStack->RemoveChip();
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

	auto deck = GetWorld()->SpawnGameObject<Deck>();
	deck->PopulateDeck();
	deck->GetTransform().Translation = { -60, 26, -100 };

	m_ChipStack = GetWorld()->SpawnGameObject<ChipStack>();
	m_ChipStack->SetLocation({0, -30});




}

void GameplayGameMode::LeaveGame()
{
	AudioSystem::StopMusic();
	AudioSystem::StopAllSounds();
	World::OpenScene<MenuScene>();
}


