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
		m_ViewportWidth = width;
		m_ViewportHeight = height;
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

	CameraInfo Camera::GetCameraInfo() const
	{
		CameraInfo info;
		info.ProjectionMatrix = m_ProjectionMatrix;
		return info;
	}

	void Camera::RecalculateProjection()
	{
		float ortholeft = -m_Size  * 0.5f;
		float orthoRight = m_Size  * 0.5f;
		float orthoBottom = -m_Size * 0.5f;
		float orthoTop = m_Size * 0.5f;

		m_ProjectionMatrix = glm::ortho(ortholeft, orthoRight, orthoBottom, orthoTop);
		float scale = m_ViewportHeight / 2;

		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, 1.0f));
		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ViewportWidth / 2.0f, m_ViewportHeight / 2.0f, 0.0f));
		m_ProjectionMatrix = translateMatrix * scaleMatrix * m_ProjectionMatrix;
	}

}