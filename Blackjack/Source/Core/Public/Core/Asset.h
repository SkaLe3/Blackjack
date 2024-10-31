#pragma once
#include "Core/CoreDefines.h"



namespace Core
{

	class SoundBase;
	class Texture;

	enum class AssetType
	{
		None = 0,
		ATexture = 1 << 0,
		ASound = 1 << 1,
		ASoundCue = ASound | (1 << 2),
		ASoundMusic = ASound | (1 << 3)
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
		SharedPtr<SoundBase> SoundP;
		ASSET_CLASS_TYPE(ASound);
	};
}