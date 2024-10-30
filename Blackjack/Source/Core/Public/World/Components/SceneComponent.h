#pragma once
#include "World/Components/GameComponent.h"
#include <glm/glm.hpp>

namespace Core
{
	class SceneComponent : public GameComponent
	{
	public:
		Transform& GetTransform(); /** Returns Transform relative to parent */
		Transform GetWorldTransform(); /** Returns Transform relative to World origin */
		glm::mat4 GetTransformMatrix();
		void SetupAttachment(WeakPtr<SceneComponent> component);
		void DetachFromParent();

	protected:
		/** Transform is relative to the parent unless there is none */
		Transform m_Transform;
		WeakPtr<SceneComponent> m_Parent;
	};
}