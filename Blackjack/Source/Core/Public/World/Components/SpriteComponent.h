#pragma once
#include "World/Components/SceneComponent.h"

namespace Core
{
	class Sprite;
	class TextureAtlas;

	class SpriteComponent : public SceneComponent
	{
		DECLARE_SUPER(SceneComponent)
	public:
		SpriteComponent();
		~SpriteComponent() = default;

		bool HasAtlas();
		SharedPtr<Sprite> GetSprite();
		SharedPtr<TextureAtlas> GetAtlas();
		void UpdateAtlas();

		void SetSprite(SharedPtr<Sprite> inSprite);
		void SetAtlas(SharedPtr<TextureAtlas> inAtlas);
		void SetRegion(const String& name);

		void FlipHorizontal();
		void FlipVertical();
		void FlipNone();

	private:
		SharedPtr<Sprite> m_Sprite;
		SharedPtr<TextureAtlas> m_Atlas;
		bool m_bUseAtlas;
	};
}