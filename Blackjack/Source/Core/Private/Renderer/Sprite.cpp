#include "Renderer/Sprite.h"

namespace Core
{

	SharedPtr<Sprite> Sprite::Create(SharedPtr<Texture> inTexture, const glm::vec2& inSrcSize, const glm::vec2& inSrcPos)
	{
		return MakeShared<Sprite>(inTexture, inSrcSize, inSrcPos);
	}

	SharedPtr<Sprite> Sprite::Create(SharedPtr<Texture> inTexture)
	{
		return MakeShared<Sprite>(inTexture, inTexture->GetSize(), glm::vec2{ 0, 0 });
	}

	Sprite::Sprite(SharedPtr<Texture> inTexture, const glm::vec2& inSrcSize, const glm::vec2& inSrcPos)
		: m_Texture(inTexture), m_SourceSize(inSrcSize), m_SourcePos(inSrcPos), m_bVisible(true)
	{}


	void Sprite::MapToAtlas(const glm::vec4& region)
	{
		m_SourcePos = { region.x, region.y };
		m_SourceSize = { region.z, region.w };
	}

}