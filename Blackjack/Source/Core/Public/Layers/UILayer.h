#pragma once
#include "Core/CoreDefines.h"
#include "Core/Event.h"

#include "Layers/Layer.h"


namespace Core
{
	class UILayer : public Layer
	{
	public:
		UILayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(float deltaTime) override;
		void OnEvent(Event& event) override;

	private:
		// PlayerLayer should contain these
		//SharedPtr<Overlay> Widget;
		//Canvas::Slot* Slot;

		//SceneViewport
	};
}