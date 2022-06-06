#pragma once
#include "Component.h"

namespace dae
{
	class Transform final
	{
	public:
		Transform() = default;
		Transform(dae::GameObject* pGO);
		~Transform();

		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;


		//Getters
		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();

		//Setters
		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(const glm::vec3& pos);
		void SetDirty();
	private:
		//Update
		void UpdateWorldPosition();

		dae::GameObject* m_pOwner;
		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;
		bool m_PositionIsDirty = false;
	};
}
