#include "World/Components/QuadComponent.h"

namespace Core
{

	void QuadComponent::Destroy()
	{
		// TODO: Destroy
	}

	glm::vec2 QuadComponent::GetHalfSize() const
	{
		return m_QuadHalfSize;
	}

	void QuadComponent::SetHalfSize(const glm::vec2& inSize)
	{
		m_QuadHalfSize = inSize;
	}

}