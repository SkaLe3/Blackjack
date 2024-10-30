#pragma once
#include "Renderer/Texture.h"

#include <glm/glm.hpp>
#include <unordered_map>

namespace Core
{
	class TextureAtlas
	{
	public:
		TextureAtlas(SharedPtr<Texture> inTexture);

		void AddRegion(const String& name, const glm::vec4 rect);
		glm::vec4 GetRegion(const String& name) const;

		inline SharedPtr<Texture> GetTexture() const { m_Texture; }

	private:
		SharedPtr<Texture> m_Texture;
		std::unordered_map<String, glm::vec4> m_Regions;
	};
}