#include "World/Entities/GameObject.h"
#include "World/Components/BoxComponent.h"
#include "World/World/World.h"

namespace Core
{

	GameObject::GameObject()
		: m_Tag("")
	{
		m_BoxComponent = CreateComponent<BoxComponent>();
		m_RootComponent = m_BoxComponent;
	}

	void GameObject::BeginPlay()
	{
		if (auto box = m_BoxComponent.lock())
		{
			box->SetOwner(GetSelf());
		}
	}

	void GameObject::Destroy()
	{
		GetWorld()->DestroyObject(GetSelf());
		if (auto box = m_BoxComponent.lock())
		{
			box->Destroy();
		}
	}

	Transform& GameObject::GetTransform()
	{
		if (auto root = m_RootComponent.lock())
			return root->GetTransform();
		else
			BJ_ASSERT(false, "Root component should be always valid!");
	}

	Transform GameObject::GetWorldTransform() const
	{
		if (auto root = m_RootComponent.lock())
			return root->GetWorldTransform();
		else
			BJ_ASSERT(false, "Root component should be always valid!");
	}

	SharedPtr<BoxComponent> GameObject::GetBoxComponent()
	{
		return m_BoxComponent.lock();
	}

	glm::vec2 GameObject::GetLocation()
	{
		if (auto root = m_RootComponent.lock())
			return glm::vec2(root->GetWorldTransform().Translation);
		else
			return glm::vec2();
	}

	String GameObject::GetTag()
	{
		return m_Tag;
	}

	void GameObject::AttachToObject(WeakPtr<GameObject> parentObject)
	{
		auto parent = parentObject.lock();
		if (!parent)
			return;
		if (GetSelf().lock() == parent)
			return;

		this->DetachFromObject();

		if (SharedPtr<SceneComponent> rootComp = GetRoot())
		{
			rootComp->SetupAttachment(parent->GetRoot());
		}
	}

	void GameObject::DetachFromObject()
	{
		if (SharedPtr<SceneComponent> rootComp = GetRoot())
		{
			rootComp->DetachFromParent();
		}
	}

	void GameObject::SetRoot(WeakPtr<SceneComponent> root)
	{
		m_RootComponent = root;
	}

	void GameObject::SetLocation(const glm::vec2 location)
	{
		if (auto box = m_BoxComponent.lock())
		{
			Transform worldTransform = GetWorldTransform();
			Transform& relativeTransform = GetTransform();
			glm::vec2 result = glm::vec2(relativeTransform.Translation) 
							 - glm::vec2(worldTransform.Translation) 
							 + location;
			relativeTransform.Translation = glm::vec3(result, relativeTransform.Translation.z);	
		}
	}

	void GameObject::SetTag(const String& tag)
	{
		m_Tag = tag;
	}

}