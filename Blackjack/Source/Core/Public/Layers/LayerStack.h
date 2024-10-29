#pragma once

#include "Core/CoreDefines.h"
#include "Layers/Layer.h"

#include <vector>
#include <memory>

namespace Core
{
	class LayerStack
	{
	public:
		using iterator_vec = std::vector<SharedPtr<Layer>>::iterator;
		using const_iterator_vec = std::vector<SharedPtr<Layer>>::const_iterator;

	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(const SharedPtr<Layer> layer);
		void PopLayer(const SharedPtr<Layer> layer);

		void Clear();

		inline iterator_vec begin() {return m_Layers.begin();}
		inline const_iterator_vec begin() const {return m_Layers.begin();}
		inline iterator_vec end() {return m_Layers.end();}
		inline const_iterator_vec end() const {return m_Layers.end();}

	private:
		std::vector<SharedPtr<Layer>> m_Layers;
	};
}