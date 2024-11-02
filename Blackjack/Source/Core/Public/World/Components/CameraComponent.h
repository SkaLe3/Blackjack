#pragma once
#include "World/Components/SceneComponent.h"
#include "Renderer/Camera.h"

namespace Core
{
	class CameraComponent : public SceneComponent
	{
		DECLARE_SUPER(GameComponent)
	public:
		CameraComponent() : m_bPrimary(true) { m_Camera = MakeShared<Camera>(); }

		SharedPtr<Camera> GetCamera() { return m_Camera; }

	private:
		SharedPtr<Camera> m_Camera;
		bool m_bPrimary;
	};

}