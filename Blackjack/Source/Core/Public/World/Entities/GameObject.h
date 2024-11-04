#pragma once
#include "World/Entities/Object.h"
#include "World/World/World.h"

namespace Core
{
	class SceneComponent;
	class BoxComponent;
	
	/*
	 * Note: Objects inheriting from this class should be stored as WeakPtr in other objects,
	 *       or ensure that cyclic dependencies are avoided.
	 */

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
		SharedPtr<T> CreateComponent()
		{
			//return MakeShared<T>();
			return GetWorld()->CreateComponent<T>();
		}

		inline WeakPtr<GameObject> GetSelf() { return weak_from_this(); }
		Transform& GetTransform();
		Transform GetWorldTransform() const;
		SharedPtr<BoxComponent> GetBoxComponent();
		inline SharedPtr<SceneComponent> GetRoot() { return m_RootComponent.lock(); }
		glm::vec2 GetLocation(); /** Location relative to World origin */
		String GetTag();

		/* 
		* Current object transform will become relative to the parent.
		* Might be reasonable to calculate relative transform instead
		*/
		void AttachToObject(WeakPtr<GameObject> parentObject);
		void DetachFromObject();
		SharedPtr<GameObject> GetOwner();
		void SetRoot(WeakPtr<SceneComponent> root);

		/*
		* This function sets the location relative to the world origin.
		* Use Transform to change the translation relative to the parent.
		*
		* Important: Use this function to set the location relative to the world origin
		* only after attaching to the object. Otherwise, the set location will be relative to the object.
		*/
		void SetLocation(const glm::vec2 location);
		void SetTag(const String& tag);

	protected:
		WeakPtr<SceneComponent> m_RootComponent;
		WeakPtr<BoxComponent> m_BoxComponent;

		String m_Tag;

	};
}