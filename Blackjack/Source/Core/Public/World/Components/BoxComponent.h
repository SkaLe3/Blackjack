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

		 //~ Begin Object Interface
		 virtual void BeginPlay() override {}
		 virtual void Tick(float deltaTime) override {}
		 virtual void EndPlay() override {}
		 virtual void Destroy() override;
		 //~ End Object Interface

		 glm::vec2 GetHalfSize() const;
		 void SetHalfSize(const glm::vec2& inSize);

	private:
		glm::vec2 m_QuadHalfSize;
	};
}