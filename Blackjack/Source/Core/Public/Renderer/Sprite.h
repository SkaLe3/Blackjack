#pragma once
#include "Renderer/Texture.h"

#include <glm/glm.hpp>

namespace Core
{
	class SceneRenderer;

	class Sprite
	{
	public:
		static SharedPtr<Sprite> Create(SharedPtr<Texture> inTexture, const glm::vec2& inSrcSize, const glm::vec2& inSrcPos);
		static SharedPtr<Sprite> Create(SharedPtr<Texture> inTexture);
		Sprite(SharedPtr<Texture> inTexture, const glm::vec2& inSrcSize, const glm::vec2& inSrcPos);

		void MapToAtlas(const glm::vec4& region);
	protected:
		SharedPtr<Texture> m_Texture;
		glm::vec2 m_SourceSize;
		glm::vec2 m_SourcePos;

		friend SceneRenderer;
	};
}