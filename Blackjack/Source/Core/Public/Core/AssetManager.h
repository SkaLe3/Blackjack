#pragma once
#include "Core/CoreDefines.h"
#include "Core/Asset.h"
#include "Renderer/Texture.h"
#include "Sound/Sound.h"

#include <filesystem>
#include <unordered_map>
#include <thread>
#include <future>

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

		template<typename T>
		SharedPtr<T> Load(const String& assetName);
		template<typename T>
		std::future<SharedPtr<T>> LoadAssetAsync(const String& assetName);
		void Unload(const String& assetName);
		/** Should be called on a scene change */
		void ClearCache();

	private:
		SharedPtr<Texture> CreateTextureFromFile(const String& filePath);
		SharedPtr<SoundCue>	CreateSoundCueFromFile(const String& filePath);

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
		{
			auto soundAsset = MakeShared<SoundAsset>();
			soundAsset->SoundP = CreateSoundCueFromFile(m_Registry[assetName].string());
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

}