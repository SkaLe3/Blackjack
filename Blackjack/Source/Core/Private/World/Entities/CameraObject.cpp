#include "World/Entities/CameraObject.h"

namespace Core
{

	CameraObject::CameraObject()
	{
		m_CameraComponent = CreateComponent<CameraComponent>();
		auto camera = GetCameraComponent();
		camera->SetupAttachment(GetBoxComponent());
		GetWorld()->UseCamera(GetCameraComponent());
	}

	void CameraObject::BeginPlay()
	{
		Super::BeginPlay();
		GetCameraComponent()->SetOwner(GetSelf());
	}

	void CameraObject::Destroy()
	{
		Super::Destroy();
		GetCameraComponent()->Destroy();
	}

}