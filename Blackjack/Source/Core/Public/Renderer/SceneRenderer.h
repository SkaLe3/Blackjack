#pragma once
#include "Core/CoreDefines.h"

#include <glm/glm.hpp>

namespace Core
{
	class Font;
	
	class SceneRenderer
	{
	public:
		static SharedPtr<SceneRenderer> Create();
		~SceneRenderer();

		void Init();
		void Shutdown();

		void BeginScene(const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix);
		void EndScene();

		void DrawSprite(glm::vec2 position, glm::vec2 size, float rotation, glm::vec4 color);
		//void DrawText();

	private:
		glm::vec2 m_ViewportSize;
		glm::vec3 m_CameraPos;
		glm::mat4 m_ViewProjection;
		glm::mat4 m_InverseView;
		
		glm::vec2 m_QuadVertexPos[4];
		float m_LineWidth = 1.0f;
		SharedPtr<Font> m_CurrentFont;
	};
}