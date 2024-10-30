#pragma once
#include "Core/CoreDefines.h"
#include "Core/Event.h"

#include "Layers/Layer.h"


// TEMPORARY
#include <SDL2/SDL.h>
#include <Renderer/Texture.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace Core
{
	class GameLayer : public Layer
	{
	public:
		GameLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(float deltaTime) override;
		void OnEvent(Event& event) override;

	private:

		// TEMPORARY
		bool OnKeyPressed(Event& event);

		bool startAnim = false;
		float elapsedTime = 0;
		float flipDuration = 0.5f;
		bool notify = false;
		bool triggered = false;
		int32 selectedFace = 0;


		glm::vec2 cardPos = {500, 300};
		glm::vec2 cardHalfsize = {109, 153};
		glm::vec2 curHalfsize = cardHalfsize;
		SharedPtr<Texture> cardTex;
	
	};
}