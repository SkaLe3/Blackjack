#pragma once
#include "Renderer/TextureAtlas.h"

class CardTextureAtlas : public Core::TextureAtlas
{
public:
	CardTextureAtlas();
	CardTextureAtlas(SharedPtr<Core::Texture> texture);
};