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

	void SceneRenderer::DrawSprite(const glm::mat4& transform, const glm::vec3& objScale, SharedPtr<Sprite> sprite)
	{
		glm::mat4 MVP = m_ViewProjection * transform;
		glm::vec4 position = MVP * glm::vec4(0, 0, 0, 1);


		/*
		* The following steps are necessary to create an accurate SDL_Rect.
		* Quad vertices should not include rotation, as rotation will be applied
		* separately through a function argument.
		*/
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Extract translation  from MVP
		glm::vec3 translation = glm::vec3(MVP[3]);

		// Extract scale along each axis
		glm::vec3 scale;
		scale.x = glm::length(glm::vec3(MVP[0]));
		scale.y = glm::length(glm::vec3(MVP[1]));
		scale.z = glm::length(glm::vec3(MVP[2]));
// 		 		float rot = atan2(MVP[1][0], MVP[0][0]);
// 		 		float rot_degrees = glm::degrees(rot);

		glm::mat4 rotMat = MVP;
		rotMat[0][0] = rotMat[0][0] / objScale.x;
		rotMat[0][1] = rotMat[0][1] / objScale.x;
		rotMat[1][0] = rotMat[1][0] / objScale.y;
		rotMat[1][1] = rotMat[1][1] / objScale.y;
		

		float rot = atan2(rotMat[1][0], rotMat[0][0]);
		float rot_degrees = glm::degrees(rot);


		// Create a matrix with only scale and translation
		glm::mat4 scaleTranslationMatrix = glm::mat4(1.0f);
		scaleTranslationMatrix[0][0] = scale.x;
		scaleTranslationMatrix[1][1] = scale.y;
		scaleTranslationMatrix[2][2] = scale.z;
		scaleTranslationMatrix[3] = glm::vec4(translation, 1.0f);
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		glm::vec4 vertices[2];
		vertices[0] = scaleTranslationMatrix * m_QuadCornerPos[0];
		vertices[1] = scaleTranslationMatrix * m_QuadCornerPos[1];

		// Find sprite size in screen coordinates
		float sizeX = vertices[1].x - vertices[0].x;
		float sizeY = vertices[1].y - vertices[0].y;

		// Offset sprite origin to its geometrical center
		glm::vec2 offset = { sizeX / 2.0f, sizeY / 2.0f };
		Renderer::DrawTexturedRect(sprite->m_Texture, { sprite->m_SourcePos, sprite->m_SourceSize }, { position.x - offset.x, position.y - offset.y, sizeX, sizeY }, { 1.f, 1.f, 1.f, 1.f }, rot_degrees, { sizeX / 2.0f, sizeY / 2.0f }, 0);

	}

	void SceneRenderer::DrawRect(const glm::mat4& transform, const glm::vec2& box, const glm::vec4& color, bool bFill)
	{
		glm::mat4 MVP = m_ViewProjection * transform;
		glm::vec4 position = MVP * glm::vec4(0, 0, 0, 1);

		/*
		* The following steps are necessary to create an accurate SDL_Rect.
		* Quad vertices should not include rotation, as rotation will be applied
		* separately through a function argument.
		*/
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Extract translation  from MVP
		glm::vec3 translation = glm::vec3(MVP[3]);

		// Extract scale along each axis
		glm::vec3 scale;
		scale.x = glm::length(glm::vec3(MVP[0]));
		scale.y = glm::length(glm::vec3(MVP[1]));
		scale.z = glm::length(glm::vec3(MVP[2]));

		// Create a matrix with only scale and translation
		glm::mat4 scaleTranslationMatrix = glm::mat4(1.0f);
		scaleTranslationMatrix[0][0] = scale.x;
		scaleTranslationMatrix[1][1] = scale.y;
		scaleTranslationMatrix[2][2] = scale.z;
		scaleTranslationMatrix[3] = glm::vec4(translation, 1.0f);
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		glm::vec4 vertices[2];
		glm::vec4 boxCorners[2] = { {-box.x, -box.y, 0, 1}, {box.x, box.y, 0, 1} };
		vertices[0] = scaleTranslationMatrix * boxCorners[0];
		vertices[1] = scaleTranslationMatrix * boxCorners[1];

		// Find sprite size in screen coordinates
		float sizeX = vertices[1].x - vertices[0].x;
		float sizeY = vertices[1].y - vertices[0].y;

		// Offset sprite origin to its geometrical center
		glm::vec2 offset = { sizeX / 2.0f, sizeY / 2.0f };

		Renderer::DrawRect({ position.x - offset.x, position.y - offset.y, sizeX , sizeY }, color, bFill);
	}

}