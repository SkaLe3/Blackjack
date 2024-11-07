#include "Renderer/ScreenRenderer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Sprite.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Core
{




	SharedPtr<ScreenRenderer> ScreenRenderer::Create(uint32 width, uint32 height)
	{
		SharedPtr<ScreenRenderer> result = MakeShared<ScreenRenderer>();
		result->Init(width, height);
		return result;
	}


	void ScreenRenderer::Init(uint32 width, uint32 height)
	{
		ScreenCamera camera;
		camera.SetViewportSize(width, height);
		camera.SetOrthoSize(1080);
		m_Projection = camera.GetProjection();  // View matrix is identity matrix
	}

	glm::vec2 ScreenRenderer::TransformCoordinates(const glm::vec2& screenCoords)
	{
		glm::vec4 viewportCoords = glm::inverse(m_Projection) * glm::vec4(screenCoords, 0, 1);
		return { viewportCoords.x, viewportCoords.y };
	}

	void ScreenRenderer::DrawWidget(const glm::vec2& transltaion, const glm::vec2& box, const glm::vec2& alignment, SharedPtr<Sprite> widget)
	{
		glm::mat4 MVP = m_Projection * glm::translate(glm::mat4(1.0f), glm::vec3{ transltaion, 0.f });
		glm::vec4 position = MVP * glm::vec4(0, 0, 0, 1);

		glm::vec4 vertices[2];
		glm::vec4 boxCorners[2] = { {0, 0, 0, 1}, {box.x, box.y, 0, 1} };
		vertices[0] = MVP * boxCorners[0];
		vertices[1] = MVP * boxCorners[1];

		// Find sprite size in screen coordinates
		glm::vec2 size = vertices[1] - vertices[0];
		glm::vec2 offset = size * alignment;

		glm::vec2 targetPosition = glm::vec2(position) - offset;

		Renderer::DrawTexturedRect(widget->m_Texture, {widget->m_SourcePos, widget->m_SourceSize},  { targetPosition, size }, { 1.f, 1.f, 1.f, 1.f }, 0, offset,0 );
	}

	void ScreenRenderer::DrawWidget(const glm::vec2& transltaion, const glm::vec2& box, const glm::vec2& alignment, const glm::vec4& color /*= {1.f, 1.f, 1.f, 1.f}*/, bool bFill /*= true*/)
	{
		glm::mat4 MVP = m_Projection * glm::translate(glm::mat4(1.0f), glm::vec3{transltaion, 0.f});
		glm::vec4 position = MVP * glm::vec4(0, 0, 0, 1);

		glm::vec4 vertices[2];
		glm::vec4 boxCorners[2] = { {0, 0, 0, 1}, {box.x, box.y, 0, 1} };
		vertices[0] = MVP * boxCorners[0];
		vertices[1] = MVP * boxCorners[1];

		// Find sprite size in screen coordinates
		glm::vec2 size = vertices[1] - vertices[0];
		glm::vec2 offset = size * alignment;

		glm::vec2 targetPosition = glm::vec2(position) - offset;

		Renderer::DrawRect({ targetPosition, size }, color, bFill);
	}







	ScreenCamera::ScreenCamera()
		: m_Size(720), m_AspectRatio(1.f), m_ProjectionMatrix(1.0f)
	{

	}

	void ScreenCamera::SetViewportSize(uint32 width, uint32 height)
	{
		m_AspectRatio = (float)width / (float)height;
		m_ViewportWidth = width;
		m_ViewportHeight = height;
		RecalculateProjection();
	}

	void ScreenCamera::SetOrthoSize(float size)
	{
		m_Size = size;
		RecalculateProjection();
	}

	glm::mat4 ScreenCamera::GetProjection() const
	{
		return m_ProjectionMatrix;
	}

	void ScreenCamera::RecalculateProjection()
	{
		float targetWidth = m_AspectRatio * m_Size;
		float targetHeight = m_Size;

		m_ProjectionMatrix = glm::ortho(0.0f, targetWidth, targetHeight, 0.0f, -1.0f, 1.0f);
		float scale = m_ViewportHeight / 2;
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale * m_AspectRatio, -scale, 1.0f));
		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(scale * m_AspectRatio, scale, 0.0f));
		m_ProjectionMatrix = translateMatrix * scaleMatrix * m_ProjectionMatrix;

	}
}