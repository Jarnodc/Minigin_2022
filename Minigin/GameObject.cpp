#include "MiniginPCH.h"
#include "GameObject.h"


void dae::GameObject::Update()
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Update();
	}
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->Update();
	}
	/*for (const auto& comp : m_pComponents)
	{
		comp->Update();
	}
	for (const auto& child : m_pChildren)
	{
		child->Update();
	}*/
}
void dae::GameObject::FixedUpdate()
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->FixedUpdate();
	}
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->FixedUpdate();
	}
	/*for (const auto& comp : m_pComponents)
	{
		comp->FixedUpdate();
	}
	for (const auto& child : m_pChildren)
	{
		child->FixedUpdate();
	}*/
}

void dae::GameObject::Render() const
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Render();
	}
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->Render();
	}
	/*for (const auto& comp : m_pComponents)
	{
		comp->Render();
	}
	for (const auto& child : m_pChildren)
	{
		child->Render();
	}*/
}

void dae::GameObject::SetPosition(float x, float y)
{
	for (const auto& pChild : m_pChildren)
	{
		const auto pos{ pChild->GetLocalPosition() - m_Transform.GetLocalPosition() };
		pChild->SetPosition(pos.x + x, pos.y + y);
	}
	m_Transform.SetLocalPosition(x, y, 0.0f);
}

void dae::GameObject::MovePosition(float x, float y)
{
	const auto curPos = m_Transform.GetLocalPosition();
	m_Transform.SetLocalPosition(x + curPos.x,y + curPos.y, curPos.z);
}

void dae::GameObject::SetParent(dae::GameObject* parent, bool keepWorldPosition)
{
	if (parent)
	{
		if (keepWorldPosition)
			m_Transform.SetLocalPosition(m_Transform.GetLocalPosition() - parent->GetWorldPosition());
		m_Transform.SetDirty();
	}
	
	m_pParent = parent;				
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	if (static_cast<unsigned>(index) > m_pChildren.size())
		return nullptr;

	return m_pChildren.at(index);
}

void dae::GameObject::RemoveChild(int index)
{
	if (static_cast<unsigned>(index) > m_pChildren.size())
		return;
	
	m_pChildren.erase(m_pChildren.begin() + index);
}

void dae::GameObject::RemoveChild(dae::GameObject* go)
{
	go->SetParent(nullptr);
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), go));
}

void dae::GameObject::AddChild(dae::GameObject* go)
{
	m_pChildren.push_back(go);
	go->SetParent(this,false);
}


dae::GameObject::~GameObject()
{
	for(auto component : m_pComponents)
	{
		delete component;
		component = nullptr;
	}
	m_pComponents.clear();
}

void dae::GameObject::ResetObject() const
{
	for (const auto& component : m_pComponents)
	{
		component->ResetComponent();
	}
}




