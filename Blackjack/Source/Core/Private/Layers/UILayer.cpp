#include "Layers/UILayer.h"

#include "Renderer/ScreenRenderer.h"
#include "Input/Input.h"
#include "Core/Event.h"


namespace Core
{


	UILayer::UILayer(uint32 viewportWidth, uint32 viewportHeight)
	{
		m_Renderer = ScreenRenderer::Create(viewportWidth, viewportHeight);
	}

	void UILayer::Init()
	{
		m_ViewportClient = MakeShared<ViewportClient>();
	}

	void UILayer::OnAttach()
	{

	}

	void UILayer::OnDetach()
	{

	}

	void UILayer::OnUpdate(float deltaTime)
	{
		m_ViewportClient->Tick(deltaTime);
		m_ViewportClient->Paint(m_Renderer);

	}

	void UILayer::OnEvent(Event& event)
	{
		glm::vec2 mousePos = Input::GetMousePosition();
		m_MousePos = m_Renderer->TransformCoordinates(mousePos);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch(SDL_MOUSEMOTION, BJ_BIND_EVENT_FN(UILayer::OnMouseMoved));
		dispatcher.Dispatch(SDL_MOUSEBUTTONDOWN, BJ_BIND_EVENT_FN(UILayer::OnButtonDown));
		dispatcher.Dispatch(SDL_MOUSEBUTTONUP, BJ_BIND_EVENT_FN(UILayer::OnButtonUp));
	}



	bool UILayer::OnMouseMoved(Event& event)
	{
		return m_ViewportClient->OnMouseMoved(event, m_MousePos);
	}

	bool UILayer::OnButtonDown(Event& event)
	{
		return m_ViewportClient->OnButtonDown(event, m_MousePos);
	}

	bool UILayer::OnButtonUp(Event& event)
	{
		return m_ViewportClient->OnButtonUp(event, m_MousePos);
	}

	SharedPtr<ViewportClient> UILayer::GetViewportClient()
	{
		 return m_ViewportClient;
	}

	SharedPtr<Core::ScreenRenderer> UILayer::GetScreenRenderer()
	{
		return m_Renderer;
	}

}