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

		//~ Begin Object Interface
		virtual void Destroy() override;
		//~ End Object Interface

		void SetSprite(SharedPtr<Sprite> inSprite);
		void SetAtlas(SharedPtr<TextureAtlas> inAtlas);

	private:
		SharedPtr<Sprite> m_Sprite;
		SharedPtr<TextureAtlas> m_Atlas;
		bool m_bUseAtlas;
	};
}