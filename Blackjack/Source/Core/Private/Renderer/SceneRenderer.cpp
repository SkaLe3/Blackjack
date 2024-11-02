#include "Renderer/SceneRenderer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Sprite.h"

namespace Core
{

	SharedPtr<SceneRenderer> SceneRenderer::Create()
	{
		SharedPtr<SceneRenderer> result = MakeShared<SceneRenderer>();
		result->Init();
		return result;
	}

	SceneRenderer::~SceneRenderer()
	{
		Shutdown();
	}

	void SceneRenderer::Init()
	{
		m_QuadCornerPos[0] = { -0.5, -0.5, 0, 1 };
		m_QuadCornerPos[1] = { 0.5, 0.5, 0, 1 };
	}

	void SceneRenderer::Shutdown()
	{

	}

	void SceneRenderer::BeginScene(const CameraInfo& cameraInfo)
	{
		m_ViewProjection = cameraInfo.ProjectionMatrix * cameraInfo.ViewMatrix;
	}

	void SceneRenderer::EndScene()
	{

	}

	void SceneRenderer::DrawSprite(const glm::mat4& transform, SharedPtr<Sprite> sprite)
	{
		glm::mat4 MVP = m_ViewProjection * transform;
		glm::vec4 position = MVP * glm::vec4(0, 0, 0, 1);

		glm::vec4 vertices[2];
		vertices[0] = MVP * m_QuadCornerPos[0];
		vertices[1] = MVP * m_QuadCornerPos[1];

		// Find sprite size in screen coordinates
		float sizeX = vertices[1].x - vertices[0].x;
		float sizeY = vertices[1].y - vertices[0].y;

		// Offset sprite origin to its geometrical center
		glm::vec2 offset = { sizeX / 2.0f, sizeY / 2.0f };
		Renderer::DrawTexturedRect(sprite->m_Texture, { sprite->m_SourcePos, sprite->m_SourceSize }, { position.x - offset.x, position.y - offset.y, sizeX, sizeY }, { 1.f, 1.f, 1.f, 1.f }, 0, { 0, 0 }, 0);

	}

}