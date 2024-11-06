#pragma once
#include "Core/CoreDefines.h"
#include "Core/Asset.h"
#include "Renderer/Texture.h"
#include "Sound/Sound.h"

#include <filesystem>
#include <unordered_map>
#include <thread>
#include <future>
#include <vector>

namespace Core
{
	/*
	* @class AssetManager
	*
	* Manages the loading, unloading, and caching of assets in the application.
	*/
	class AssetManager
	{

	public:
		AssetManager() = default;
		virtual ~AssetManager() {}

	public:
		static AssetManager& Get();
		static bool IsInitialized();

		void SetContentPath(const std::filesystem::path& path);
		std::filesystem::path GetContentPath();

		void InitialLoading();
		/** Scans content directory for asset files and registers them */
		void ScanAssets();
		void Register(const std::filesystem::path& newAsset);

		template<typename T>
		SharedPtr<T> Load(const String& assetName);
		template<typename T>
		std::future<SharedPtr<T>> LoadAssetAsync(const String& assetName);
		void Unload(const String& assetName);
		/** Should be called on a scene change */
		void ClearCache();

		std::vector<String> GetKeysWithPrefix(const String& prefix);

	private:
		SharedPtr<Texture> CreateTextureFromFile(const String& filePath);
		template<typename T>
		SharedPtr<T> CreateSoundFromFile(const String& filePath);


		/** Possible solution */
// 		template<typename T>
// 		SharedPtr<T> LoadInternal(const String& assetName);

	private:
		std::filesystem::path m_ContentPath;

		std::unordered_map<String, AssetType> m_AssetTypeMap;
		std::unordered_map<String, SharedPtr<Asset>> m_CachedRegistry;
		std::unordered_map<String, std::filesystem::path> m_Registry;
	};

	template<typename T>
	SharedPtr<T> AssetManager::Load(const String& assetName)
	{
		if (m_CachedRegistry.find(assetName) != m_CachedRegistry.end())
		{
			BJ_LOG_INFO("[AssetManager]: %s was retrieved from the cache", assetName.c_str());
			return std::dynamic_pointer_cast<T>(m_CachedRegistry[assetName]);
		}

		if (m_Registry.find(assetName) == m_Registry.end())
		{
			BJ_ASSERT(false, "[AssetManager]: Invalid asset name: %s", assetName.c_str());
		}

		BJ_LOG_INFO("[AssetManager]: %s was loaded from disk", assetName.c_str());

		SharedPtr<Asset> newAsset;
		switch (m_AssetTypeMap[assetName])
		{
		case AssetType::ATexture:
		{
			auto texAsset = MakeShared<TextureAsset>();
			texAsset->TextureP = CreateTextureFromFile(m_Registry[assetName].string());
			newAsset = texAsset;
			break;
		}
		case AssetType::ASound:
		case AssetType::ASoundCue:
		case AssetType::ASoundMusic:
		{
			auto soundAsset = MakeShared<SoundAsset>();
			if (m_AssetTypeMap[assetName] == AssetType::ASoundCue)
			{
				soundAsset->SoundP = CreateSoundFromFile<SoundCue>(m_Registry[assetName].string());
			}
			else
			{
				soundAsset->SoundP = CreateSoundFromFile<SoundMusic>(m_Registry[assetName].string());
			}
			newAsset = soundAsset;
			break;
		}
		default:
			BJ_ASSERT(false, "Usupported asset type");
			return nullptr;
		}

		m_CachedRegistry[assetName] = newAsset;
		return std::static_pointer_cast<T>(newAsset);
	}

	// 	template<typename T>
	// 	SharedPtr<T> AssetManager::LoadInternal(const String& assetName){}
	// 
	// 	template<>
	// 	SharedPtr<TextureAsset> AssetManager::LoadInternal(const String&){}
	// 	template<>
	// 	SharedPtr<SoundAsset> AssetManager::LoadInternal(const String&) {}

	template<typename T>
	std::future<SharedPtr<T>> AssetManager::LoadAssetAsync(const String& assetName)
	{
		return std::async(std::launch::async, [this, assetName]()
						  {
							  return Load(assetName);
						  });
	}

	template<typename T>
	inline SharedPtr<T> AssetManager::CreateSoundFromFile(const String& filePath)
	{
		// Should never happen;
		BJ_ASSERT(false, "Attempt to load unsupported sound type");
		return nullptr;
	}

	template<>
	inline SharedPtr<SoundCue> AssetManager::CreateSoundFromFile<SoundCue>(const String& filePath)
	{
		Mix_Chunk* loadedSound = Mix_LoadWAV(filePath.c_str());
		if (!loadedSound)
			BJ_LOG_WARN("Sound not loaded... %s", filePath.c_str());

		SharedPtr<SoundCue> sound = MakeShared<SoundCue>(loadedSound);
		return sound;
	}
	template<>
	inline SharedPtr<SoundMusic> AssetManager::CreateSoundFromFile<SoundMusic>(const String& filePath)
	{
		Mix_Music* loadedSound = Mix_LoadMUS(filePath.c_str());
		if (!loadedSound)
			BJ_LOG_WARN("Sound not loaded... %s", filePath.c_str());

		SharedPtr<SoundMusic> sound = MakeShared<SoundMusic>(loadedSound);
		return sound;
	}



}