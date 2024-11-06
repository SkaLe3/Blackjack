#include "Core/AssetManager.h"

#include "Core/Application.h"
#include "Renderer/Renderer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace fs = std::filesystem;

namespace Core
{

	AssetManager& AssetManager::Get()
	{
		AssetManager* singleton = Application::Get().m_AssetManager.get();

		BJ_ASSERT(singleton, "AssetManager doesn't exist!");
		return *singleton;
	}

	bool AssetManager::IsInitialized()
	{
		return Application::Get().m_AssetManager != nullptr;
	}

	void AssetManager::SetContentPath(const std::filesystem::path& path)
	{
		m_ContentPath = path;
	}

	fs::path AssetManager::GetContentPath()
	{
		return m_ContentPath;
	}



	void AssetManager::InitialLoading()
	{
		ScanAssets();
	}

	void AssetManager::ScanAssets()
	{
		for (const auto& entry : fs::recursive_directory_iterator(m_ContentPath))
		{
			if (fs::path entryPath = entry.path(); fs::is_regular_file(entryPath))
			{
				Register(entryPath);
			}
		}
	}

	void AssetManager::Register(const std::filesystem::path& newAsset)
	{
		if (newAsset.extension() == ".png" ||
			newAsset.extension() == ".jpg")
		{
			String assetName = "T_" + newAsset.stem().string();
			m_Registry[assetName] = newAsset;
			BJ_LOG_INFO("[AssetManager]: Loaded %s asset path for '%s' to asset registry: %s ", "Texture", assetName.c_str(), newAsset.string().c_str());

			m_AssetTypeMap[assetName] = AssetType::ATexture;
		}
		if (newAsset.extension() == ".wav" ||
			newAsset.extension() == ".mp3")
		{
			String assetName = "S_" + newAsset.stem().string();
			m_Registry[assetName] = newAsset;
			BJ_LOG_INFO("[AssetManager]: Loaded %s asset path for '%s' to asset registry: %s ", "Music", assetName.c_str(), newAsset.string().c_str());
			m_AssetTypeMap[assetName] = newAsset.extension() == ".wav" ? AssetType::ASoundCue : AssetType::ASoundMusic;
		}
	}

	void AssetManager::Unload(const String& assetName)
	{
		m_CachedRegistry.erase(assetName);
		BJ_LOG_INFO("[AssetManager]: Unloaded asset '%s' from cached registry with path: %s", assetName, m_Registry[assetName].string().c_str());
	}

	void AssetManager::ClearCache()
	{
		m_CachedRegistry.clear();
	}

	std::vector<String> AssetManager::GetKeysWithPrefix(const String& prefix)
	{
		std::vector<std::string> result;
		for (const auto& [key, value] : m_Registry)
		{
			if (key.rfind(prefix, 0) == 0)
			{
				result.push_back(key);
			}
		}
		return result;
	}

	SharedPtr<Texture> AssetManager::CreateTextureFromFile(const String& filePath)
	{
		SDL_Surface* loadedSurface = IMG_Load(filePath.c_str()); // Could be replaced with IMG_LoadTexture()
		if (!loadedSurface)
			BJ_LOG_WARN("Image not loaded... %s", filePath.c_str());

		auto texture = Renderer::CreateTextureFromSurface(loadedSurface);
		SDL_FreeSurface(loadedSurface);
		return texture;
	}





}
