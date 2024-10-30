#include "Renderer/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Core
{
	Camera::Camera() : m_Size(10.0f), m_AspectRatio(1.0f), m_ProjectionMatrix(1.0f)
	{

	}

	void Camera::SetViewportSize(uint32 width, uint32 height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	glm::mat4 Camera::GetProjection() const
	{
		return m_ProjectionMatrix;
	}

	float Camera::GetOrthoSize() const
	{
		return m_Size;
	}

	void Camera::SetOrthoSize(float size)
	{
		m_Size = size;
		RecalculateProjection();
	}

	float Camera::GetAspectRatio() const
	{
		return m_AspectRatio;
	}

	void Camera::RecalculateProjection()
	{
	   float ortholeft = -m_Size * m_AspectRatio * 0.5f;
	   float orthoRight = m_Size * m_AspectRatio * 0.5f;
	   float orthoBottom = -m_Size * 0.5f;
	   float orthoTop = m_Size * 0.5f;

	   m_ProjectionMatrix = glm::ortho(ortholeft, orthoRight, orthoBottom, orthoTop, -1.0f, 1.0f);
	}

}