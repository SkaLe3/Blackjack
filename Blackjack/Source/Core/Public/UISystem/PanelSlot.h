#pragma once
#include "Core/CoreDefines.h"

#include <glm/glm.hpp>

namespace Core
{


	struct AnchorData
	{
		glm::vec2 Size;
		glm::vec2 Position;
		glm::vec2 Alignment = glm::vec2();
	};

	class PanelWidget;
	class Widget;

	class PanelSlot
	{
	public:
		void SetLayout(const AnchorData& inLayoutData);
		AnchorData GetLayout() const;

		void SetPosition(const glm::vec2& inPosition);
		glm::vec2 GetPosition() const;

		void SetSize(const glm::vec2& inSize);
		glm::vec2 GetSize() const;

		void SetAlignment(const glm::vec2& inAlignment);
		glm::vec2 GetAlignment() const;

		void SetZOrder(int32_t inZOrder);
		int32_t GetZOrder() const;
		


	public:
		SharedPtr<PanelWidget> Parent;
		SharedPtr<Widget> Content;

	public:
		AnchorData LayoutData;
		int32 ZOrder;
	};
}