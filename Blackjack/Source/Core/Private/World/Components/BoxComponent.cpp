#include "World/Components/QuadComponent.h"

namespace Core
{

	void BoxComponent::Destroy()
	{
		// TODO: Destroy
	}

	glm::vec2 BoxComponent::GetHalfSize() const
	{
		return m_QuadHalfSize;
	}

	void BoxComponent::SetHalfSize(const glm::vec2& inSize)
	{
		m_QuadHalfSize = inSize;
	}

}