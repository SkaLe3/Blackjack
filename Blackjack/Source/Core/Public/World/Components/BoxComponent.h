#pragma once
#include "World/Components/SceneComponent.h"

#include <glm/glm.hpp>

/** USE ONLY AFTER BeginPlay */
#ifdef BJ_DEBUG
#define GET_BOX_DEBUG_COLOR() GetBoxComponent()->GetColor();  
#define SET_BOX_DEBUG_COLOR(c) GetBoxComponent()->SetColor(c);
#define GET_BOX_DEBUG_VISIBILITY() GetBoxComponent()->IsVisible();
#define SET_BOX_DEBUG_VISIBILITY(v) GetBoxComponent()->SetVisibility(v);
#endif

namespace Core
{
	class BoxComponent : public SceneComponent
	{
		DECLARE_SUPER(SceneComponent)
	public:
		BoxComponent() = default;

		glm::vec2 GetHalfSize() const;
		void SetHalfSize(const glm::vec2& inSize);

	private:
		glm::vec2 m_BoxHalfSize = { 0.5f, 0.5f };

#ifdef BJ_DEBUG
	public:
		glm::vec4 GetColor() { return m_Color; }
		void SetColor(const glm::vec4& color) { m_Color = color; }
		bool IsVisible() { return m_bVisible; }
		void SetVisibility(bool bVisible) { m_bVisible = bVisible; }

	private:
		glm::vec4 m_Color = { 1.f, 0.f, 0.f, 1.f };
		bool m_bVisible = false;
#endif
	};
}