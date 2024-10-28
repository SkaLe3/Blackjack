#include "Core/LayerStack.h"

namespace Core
{

	LayerStack::~LayerStack()
	{
		 Clear();
	}

	void LayerStack::PushLayer(const SharedPtr<Layer> layer)
	{
		 m_Layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(const SharedPtr<Layer> layer)
	{
		if (auto it = std::find(m_Layers.begin(), m_Layers.end(), layer); it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
		}
		else
		{
			BJ_LOG_ERROR("Could not pop layer: %s", layer->GetName());
		}
	}

	void LayerStack::Clear()
	{
		for (SharedPtr<Layer> layer : m_Layers)
		{
			layer->OnDetach();
		}
		m_Layers.clear();
	}

}