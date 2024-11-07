#pragma once
#include "Core/CoreDefines.h"
#include "Core/Event.h"

namespace Core
{
	class Layer
	{
	public:
	Layer(const String& name = "Layer")
		: m_Name(name) {}

	virtual ~Layer() = default;

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnEvent(Event& event) {}

	virtual void Init() {}

	inline const String& GetName() const { return m_Name; }

	protected:
		String m_Name;
	};
}