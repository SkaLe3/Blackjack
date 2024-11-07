#pragma once
#include "Core/CoreDefines.h"


#include <glm/glm.hpp>

namespace Core
{
	class ScreenCamera
	{
	public:
		ScreenCamera();
		void SetViewportSize(uint32 width, uint32 height);
		void SetOrthoSize(float size);
		glm::mat4 GetProjection() const;

	private:
		void RecalculateProjection();

	private:
		float m_Size;
		float m_AspectRatio;
		float m_ViewportWidth;
		float m_ViewportHeight;

		glm::mat4 m_ProjectionMatrix;
	};


	class Sprite;

	class ScreenRenderer
	{
	public:
		static SharedPtr<ScreenRenderer> Create(uint32 width, uint32 height);
		void Init(uint32 width, uint32 height);

		glm::vec2 TransformCoordinates(const glm::vec2& screenCoords);

		void DrawWidget(const glm::vec2& transltaion, const glm::vec2& box, const glm::vec2& alignment, SharedPtr<Sprite> widget);
		void DrawWidget(const glm::vec2& transltaion, const glm::vec2& box, const glm::vec2& alignment,
						const glm::vec4& color = { 1.f, 1.f, 1.f, 1.f }, bool bFill = true);

	private:
		glm::mat4 m_Projection;
	};
}