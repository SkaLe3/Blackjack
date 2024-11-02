#pragma once
#include "World/Components/SceneComponent.h"

#include <glm/glm.hpp>

namespace Core
{
	class BoxComponent : public SceneComponent
	{
		DECLARE_SUPER(SceneComponent)
	public:
		 BoxComponent() = default;

		 glm::vec2 GetHalfSize() const;
		 void SetHalfSize(const glm::vec2& inSize);

	private:
		glm::vec2 m_BoxHalfSize = {0.5f, 0.5f};
	};
}