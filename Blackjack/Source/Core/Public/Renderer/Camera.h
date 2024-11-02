#pragma once
#include "Core/CoreDefines.h"

#include <glm/glm.hpp>

namespace Core
{

	struct CameraInfo
	{
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionMatrix;
	};

	/*
	* Camera has only orthographic mode
	* Should be used for Scene rendering
	*/
	class Camera
	{
	public:
		Camera();

		void SetViewportSize(uint32 width, uint32 height);
		glm::mat4 GetProjection() const;
		float GetOrthoSize() const;
		void SetOrthoSize(float size);
		float GetAspectRatio() const;

		CameraInfo GetCameraInfo() const;

	private:
		void RecalculateProjection();

	private:
		/** Stands for vertical size*/
		float m_Size;
		float m_AspectRatio;
		float m_ViewportWidth;
		float m_ViewportHeight;

		glm::mat4 m_ProjectionMatrix;
	};
}