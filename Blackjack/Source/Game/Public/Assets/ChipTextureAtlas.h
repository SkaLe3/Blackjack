#pragma once
#include <Renderer/TextureAtlas.h>

class ChipTextureAtlas : public Core::TextureAtlas
{
public:
	ChipTextureAtlas();
	ChipTextureAtlas(SharedPtr<Core::Texture> texture);
};