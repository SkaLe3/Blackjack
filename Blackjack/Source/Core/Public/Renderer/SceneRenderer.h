#pragma once
#include "Core/CoreDefines.h"
#include "Renderer/Camera.h"

#include <glm/glm.hpp>

namespace Core
{
	class Font;
	class Sprite;
	
	class SceneRenderer
	{
	public:
		static SharedPtr<SceneRenderer> Create();
		~SceneRenderer();

		void Init();
		void Shutdown();

		void BeginScene(const CameraInfo& cameraInfo);
		void EndScene();

		void DrawSprite(const glm::mat4& transform, SharedPtr<Sprite> sprite);
		//void DrawText();

	private:
		glm::vec2 m_ViewportSize;
		glm::vec3 m_CameraPos;
		glm::mat4 m_ViewProjection;
		glm::mat4 m_InverseView;
		
		glm::vec4 m_QuadCornerPos[2];
		float m_LineWidth = 1.0f;
		SharedPtr<Font> m_CurrentFont;
	};
}