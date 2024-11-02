#pragma once
#include "World/Entities/GameObject.h"
#include "World/Components/CameraComponent.h"

namespace Core
{
	class CameraObject : public GameObject
	{
		DECLARE_SUPER(GameObject)
	public:
		CameraObject();

		//~Begin Object Interface
		virtual void BeginPlay() override;
		virtual void Destroy() override;
		//~End Object Interface

		SharedPtr<CameraComponent> GetCameraComponent() const { return m_CameraComponent.lock(); }

	private:
		WeakPtr<CameraComponent> m_CameraComponent;
	};
}