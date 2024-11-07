#include "UISystem/PanelSlot.h"


namespace Core
{

	void PanelSlot::SetLayout(const AnchorData& inLayoutData)
	{
		LayoutData = inLayoutData;
	}

	AnchorData PanelSlot::GetLayout() const
	{
		return LayoutData;
	}

	void PanelSlot::SetPosition(const glm::vec2& inPosition)
	{
		LayoutData.Position = inPosition;
	}

	glm::vec2 PanelSlot::GetPosition() const
	{
		return LayoutData.Position;
	}

	void PanelSlot::SetSize(const glm::vec2& inSize)
	{
		 LayoutData.Size = inSize;
	}

	glm::vec2 PanelSlot::GetSize() const
	{
		return LayoutData.Size;
	}

	void PanelSlot::SetAlignment(const glm::vec2& inAlignment)
	{
		LayoutData.Alignment = inAlignment;
	}

	glm::vec2 PanelSlot::GetAlignment() const
	{
		return LayoutData.Alignment;
	}

	void PanelSlot::SetZOrder(int32_t inZOrder)
	{
		ZOrder = inZOrder;
	}

	int32_t PanelSlot::GetZOrder() const
	{
		return ZOrder;
	}

}