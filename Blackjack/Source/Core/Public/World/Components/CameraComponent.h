#pragma once
#include "World/Components/SceneComponent.h"
#include "Renderer/Camera.h"

namespace Core
{
	class CameraComponent : public SceneComponent
	{
		DECLARE_SUPER(GameComponent)
	public:
		CameraComponent() = default;

		//~Begin Object Interface
		virtual void BeginPlay() override {}
		virtual void Tick(float deltaTime) override {}
		virtual void EndPlay() override {}
		virtual void Destroy() override {}
		//~End Object Interface

	private:
		SharedPtr<Camera> m_Camera;
		bool m_bPrimary;
	};
}