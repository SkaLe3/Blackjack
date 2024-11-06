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

		void SetVisibility(bool bVisible) { m_bVisible = bVisible; }
		bool IsVisible() const { return m_bVisible; }
		void SetFlip(byte flip) { m_Flip = flip; }
		byte GetFlip() const { return m_Flip; }

		void ChangeTexture(SharedPtr<Texture> texture);
	protected:
		SharedPtr<Texture> m_Texture;
		glm::vec2 m_SourceSize;
		glm::vec2 m_SourcePos;

		bool m_bVisible;
		byte m_Flip; // 0: none, 1: horizontal, 2: vertical 

		friend SceneRenderer;
	};
}