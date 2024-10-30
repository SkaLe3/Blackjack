#include "World/Entities/GameObject.h"

namespace Core
{

	GameObject::GameObject()
		: m_Tag("")
	{
		m_QuadComponent = CreateComponent<BoxComponent>();
		m_RootComponent = m_QuadComponent;
	}

	void GameObject::BeginPlay()
	{
		if (auto quad = m_QuadComponent.lock())
		{
			quad->SetOwner(GetSelf());
		}
	}

	void GameObject::Destroy()
	{
		// TODO: Destroy self in scene
		if (auto quad = m_QuadComponent.lock())
		{
			quad->Destroy();
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

	SharedPtr<BoxComponent> GameObject::GetQuadComponent()
	{
		return m_QuadComponent.lock();
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
		if (auto quad = m_QuadComponent.lock())
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