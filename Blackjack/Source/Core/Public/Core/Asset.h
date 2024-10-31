#pragma once

#include "Core/CoreDefines.h"
#include "Renderer/Texture.h"
#include "Sound/Sound.h"


namespace Core
{

	enum class AssetType
	{
		None = 0,
		ATexture,
		ASound
	};

#define ASSET_CLASS_TYPE(type) static AssetType GetStaticType() { return AssetType::type; } \
							   virtual AssetType GetAssetType() const override { return GetStaticType(); }

	class Asset
	{
	public:
		virtual ~Asset() = default;
		virtual AssetType GetAssetType() const = 0;
	};


	class TextureAsset : public Asset
	{
	public:
		SharedPtr<Texture> TextureP;
		ASSET_CLASS_TYPE(ATexture);
	};

	class SoundAsset : public Asset
	{
	public:
		SharedPtr<SoundCue> SoundP;
		ASSET_CLASS_TYPE(ASound);
	};
}