#pragma once
#include "World/Components/SceneComponent.h"

#include <glm/glm.hpp>

namespace Core
{
	class QuadComponent : public SceneComponent
	{
	public:
		 QuadComponent() = default;

		 //~ Begin Object Interface
		 virtual void Destroy() override;
		 //~ End Object Interface

		 glm::vec2 GetHalfSize() const;
		 void SetHalfSize(const glm::vec2& inSize);

	private:
		glm::vec2 m_QuadHalfSize;
	};
}