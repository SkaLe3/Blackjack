#pragma once
#include "Renderer/Texture.h"

#include <glm/glm.hpp>

namespace Core
{
	class SceneRenderer;

	class Sprite
	{
	public:
		Sprite(SharedPtr<Texture> inTexture, glm::vec2 inSrcSize, glm::vec2 inSrcPos);
		Sprite(SharedPtr<Texture> inTexture);

	protected:
		SharedPtr<Texture> m_Texture;
		glm::vec2 m_SourceSize;
		glm::vec2 m_SourcePos;

		friend SceneRenderer;
	};
}