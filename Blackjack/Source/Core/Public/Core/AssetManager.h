#pragma once
#include "Core/CoreDefines.h"
#include "Core/Asset.h"
#include "Renderer/Texture.h"

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
			return std::dynamic_pointer_cast<T>(m_CachedRegistry[assetName]);
		}

		if (m_Registry.find(assetName) == m_Registry.end())
		{
			BJ_ASSERT(false, "Invalid asset name: %s", assetName.c_str());
		}

		switch (m_AssetTypeMap[assetName])
		{
		case AssetType::ATexture:
		{
			auto newAsset = MakeShared<TextureAsset>();
			newAsset->TextureP = CreateTextureFromFile(m_Registry[assetName].string());
			return newAsset;
		}
		case AssetType::ASound:
			BJ_ASSERT(false, "Sound assets do not supported yet!");
			break;
		}
	}

	template<typename T>
	std::future<SharedPtr<T>> AssetManager::LoadAssetAsync(const String& assetName)
	{
		return std::async(std::launch::async, [this, assetName]()
						  {
							  return Load(assetName);
						  });
	}

}