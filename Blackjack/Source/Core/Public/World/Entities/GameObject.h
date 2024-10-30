#pragma once
#include "World/Entities/Object.h"
#include "World/Components/QuadComponent.h"


namespace Core
{
	class SceneComponent;
	class QuadComponent;
	
	class GameObject : public Object, public std::enable_shared_from_this<GameObject>
	{
		DECLARE_SUPER(Object)
	public:
		GameObject();
		
		//~ Begin Object Interface
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override {}
		virtual void EndPlay() override {}
		virtual void Destroy() override;
		//~ End Object Interface

		template<typename T>
		WeakPtr<T> CreateComponent()
		{
			return MakeShared<T>(); // TODO: Create component
		}

		inline WeakPtr<GameObject> GetSelf() { return weak_from_this(); }
		Transform& GetTransform();
		Transform GetWorldTransform() const;
		SharedPtr<QuadComponent> GetQuadComponent();
		inline SharedPtr<SceneComponent> GetRoot() { return m_RootComponent.lock(); }
		glm::vec2 GetLocation(); /** Location relative to World origin */
		String GetTag();

		/* 
		* This object transform will become relative to the parent.
		* Might be reasonable to calculate relative transform instead
		*/
		void AttachToObject(WeakPtr<GameObject> parentObject);
		void DetachFromObject();
		void SetRoot(WeakPtr<SceneComponent> root);

		/*
		* This function sets location relative to World origin.
		* Use Transform to change Translation relative to parent
		*/
		void SetLocation(const glm::vec2 location);
		void SetTag(const String& tag);

	protected:
		WeakPtr<SceneComponent> m_RootComponent;
		WeakPtr<QuadComponent> m_QuadComponent;

		String m_Tag;

	};
}