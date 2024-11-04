#include "World/Components/SceneComponent.h"

namespace Core
{

	Transform& SceneComponent::GetTransform()
	{
		return m_Transform;
	}

	Transform SceneComponent::GetWorldTransform()
	{
		if (auto parent = m_Parent.lock())
			return parent->GetWorldTransform() * m_Transform;
		return m_Transform;
	}

	glm::mat4 SceneComponent::GetTransformMatrix()
	{
		if (auto parent = m_Parent.lock())
			return parent->GetTransformMatrix() * m_Transform.ToMat4();
		return m_Transform.ToMat4();
	}


	void SceneComponent::SetupAttachment(WeakPtr<SceneComponent> component)
	{
		m_Parent = component;
	}

	void SceneComponent::DetachFromParent()
	{
		m_Parent.reset();
	}

	WeakPtr<SceneComponent> SceneComponent::GetParent()
	{
	   return m_Parent;
	}

}