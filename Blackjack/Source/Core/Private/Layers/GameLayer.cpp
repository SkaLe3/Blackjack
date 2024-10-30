#include "Layers/GameLayer.h"

#include "Core/AssetManager.h"

// TEMPORARY
#include "Renderer/Renderer.h"

namespace Core
{

	GameLayer::GameLayer()
	{

	}

	void GameLayer::OnAttach()
	{
		cardTex = AssetManager::Get().Load<TextureAsset>("T_CardBlackSkin")->TextureP;
	}

	void GameLayer::OnDetach()
	{

	}

	void GameLayer::OnUpdate(float deltaTime)
	{
		if (startAnim)
		{
			elapsedTime += deltaTime;
			if (elapsedTime < flipDuration * 2)
			{
				float t = elapsedTime / flipDuration;
				float f = glm::abs(glm::cos(t * glm::pi<float>() / 2));

				curHalfsize.x = f * cardHalfsize.x;
				if (elapsedTime >= flipDuration && !notify)
				{
					notify = true;
					triggered = true;
					selectedFace = !selectedFace;
				}

				if (triggered)
				{
					if (selectedFace)
					{
						cardTex = AssetManager::Get().Load<TextureAsset>("T_CardKing")->TextureP;
					}
					else
					{
						cardTex = AssetManager::Get().Load<TextureAsset>("T_CardBlackSkin")->TextureP;
					}
					triggered = false;
				}
			}
			if (elapsedTime >= flipDuration * 2)
			{
				startAnim = false;
				curHalfsize = cardHalfsize;
				elapsedTime = 0;
				notify = false;
				triggered = false;
			}
		}


		SDL_Rect card{ cardPos.x - curHalfsize.x, cardPos.y - curHalfsize.y, curHalfsize.x * 2, curHalfsize.y * 2 };
		SDL_RenderCopy(Renderer::DebugGetRenderer(), cardTex->GetInternal(), NULL, &card);
	}

	void GameLayer::OnEvent(Event& event)
	{
		EventDispatcher disp(event);
		disp.Dispatch(SDL_KEYDOWN, BJ_BIND_EVENT_FN(GameLayer::OnKeyPressed));
	}

	bool GameLayer::OnKeyPressed(Event& event)
	{
		if (event.Ev.key.keysym.sym == SDLK_SPACE)
		{
			startAnim = true;
		}
		if (event.Ev.key.keysym.sym == SDLK_r)
		{
			curHalfsize = cardHalfsize;
		}
		return true;
	}

}