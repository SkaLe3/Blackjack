#pragma once
#include "Core/CoreDefines.h"
#include "Core/Event.h"

#include "Layers/Layer.h"
#include "UISystem/ViewportClient.h"


namespace Core
{
	class ScreenRenderer;

	class UILayer : public Layer
	{
	public:
		UILayer(uint32 viewportWidth, uint32 viewportHeight);

		void Init() override;
		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(float deltaTime) override;
		void OnEvent(Event& event) override;

		bool OnMouseMoved(Event& event);
		bool OnButtonDown(Event& event);
		bool OnButtonUp(Event& event);


		SharedPtr<ViewportClient> GetViewportClient();

	private:
		SharedPtr<ViewportClient> m_ViewportClient;
		SharedPtr<ScreenRenderer> m_Renderer;

		glm::vec2 m_MousePos;

		// PlayerLayer should contain these
		//SharedPtr<Overlay> Widget;
		//Canvas::Slot* Slot;

		//SceneViewport
	};
}