#include "World/Components/BoxComponent.h"

namespace Core
{

	void BoxComponent::Destroy()
	{
		// TODO: Destroy
	}

	glm::vec2 BoxComponent::GetHalfSize() const
	{
		return m_BoxHalfSize;
	}

	void BoxComponent::SetHalfSize(const glm::vec2& inSize)
	{
		m_BoxHalfSize = inSize;
	}

}