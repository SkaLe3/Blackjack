#include "World/Components/BoxComponent.h"
#include "World/World/World.h"

namespace Core
{


	glm::vec2 BoxComponent::GetHalfSize() const
	{
		return m_BoxHalfSize;
	}

	void BoxComponent::SetHalfSize(const glm::vec2& inSize)
	{
		m_BoxHalfSize = inSize;
	}

}