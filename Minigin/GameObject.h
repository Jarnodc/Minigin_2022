#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"
#include <vector>
#define Tag std::string

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final : public SceneObject
	{
	public:
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		//Transform
		void SetPosition(float x, float y);
		void MovePosition(float x, float y = 0);
		glm::vec3 GetLocalPosition() const { return m_Transform.GetLocalPosition(); }
		glm::vec3 GetWorldPosition() { return m_Transform.GetWorldPosition(); }

		//Update Component 
		template <typename T> T* AddComponent();
		Component* AddComponent(Component* component);
		template <typename T> T* GetComponent() const;
		template <typename T> T* GetComponents() const;
		template <typename T> void RemoveComponent();
		template <typename T> void RemoveComponent(Component* pComp);

		//Update Parent 
		void SetParent(dae::GameObject* parent, bool keepWorldPosition = false);
		dae::GameObject* GetParent() const;

		//Update Child 
		size_t GetChildCount() const;
		dae::GameObject* GetChildAt(int index) const;
		void RemoveChild(int index);
		void RemoveChild(dae::GameObject* go);
		void AddChild(dae::GameObject* go);

		//constructor / destructor
		GameObject(Tag tag = "Null"):SceneObject(),m_Transform(this),m_Tag{tag}{}
		~GameObject() override;

		//rule 5
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void ResetObject() const;

		//Tag
		Tag GetTag() const { return m_Tag; }
		void SetTag(Tag tag) { m_Tag = tag; }
	private:
		Transform m_Transform;
		std::vector<Component*> m_pComponents{};
		std::vector<dae::GameObject*> m_pChildren{};
		dae::GameObject* m_pParent{ nullptr };
		Tag m_Tag{"Null"};
	};
	
	template<typename T>
	inline T* GameObject::AddComponent()
	{
		auto pComp{ new T(this)};
		m_pComponents.push_back(pComp);
		return pComp;
	}

	inline Component* GameObject::AddComponent(Component* component)
	{
		m_pComponents.push_back(component);
		return component;
	}

	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		for (auto comp : m_pComponents)
		{
			if (typeid(*comp) == typeid(T))
			{
				return static_cast<T*>(comp);
			}
		}
		return nullptr;
	}

	template<typename T>
	inline T* GameObject::GetComponents() const
	{
		std::vector<T*> components{};
		for(auto comp : m_pComponents)
		{
			if (typeid(*comp) == typeid(T))
				components.push_back(static_cast<T*>(comp));
		}
		return components;
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		const auto pComp{ GetComponent<T>() };
		
		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), pComp));
	}
	template<typename T>
	inline void GameObject::RemoveComponent(Component* pComp)
	{
		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), pComp));
	}
}
