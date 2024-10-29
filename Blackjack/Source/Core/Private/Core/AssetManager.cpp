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
				if (entryPath.extension() == ".png" ||
					entryPath.extension() == ".jpg")
				{
					String assetName = "T_" + entryPath.stem().string();
					m_Registry[assetName] = entryPath;
					BJ_LOG_INFO("Loaded %s asset '%s' from path: %s", "Texture", assetName.c_str(), entryPath.string().c_str());

					m_AssetTypeMap[assetName] = AssetType::ATexture;
				}
				// TODO: Check for sound assets
			}
		}
	}

	void AssetManager::Unload(const String& assetName)
	{
		m_CachedRegistry.erase(assetName);
		BJ_LOG_INFO("Unloaded asset '%s' with path: %s", assetName, m_Registry[assetName].string().c_str());
	}

	void AssetManager::ClearCache()
	{
		m_CachedRegistry.clear();
	}

	SharedPtr<Texture> AssetManager::CreateTextureFromFile(const String& filePath)
	{
		SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
		if (!loadedSurface)
			BJ_LOG_WARN("Image not loaded... %s", filePath.c_str());

		auto texture = Renderer::CreateTextureFromSurface(loadedSurface);
		SDL_FreeSurface(loadedSurface);
		return texture;
	}

}
