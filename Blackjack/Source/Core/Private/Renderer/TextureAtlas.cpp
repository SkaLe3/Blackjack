#include "Renderer/TextureAtlas.h"

namespace Core
{

	TextureAtlas::TextureAtlas(SharedPtr<Texture> inTexture)
		: m_Texture(inTexture)
	{

	}

	void TextureAtlas::AddRegion(const String& name, const glm::vec4 rect)
	{
		m_Regions[name] = rect;
	}

	glm::vec4 TextureAtlas::GetRegion(const String& name) const
	{
		auto it = m_Regions.find(name);
		return (it != m_Regions.end()) ? it->second : glm::vec4(0, 0, 0, 0);
	}

}