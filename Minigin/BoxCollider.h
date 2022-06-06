#pragma once
#include "Component.h"
class BoxCollider final: public Component
{
	public:
		BoxCollider(dae::GameObject* pGO, SDL_Rect rect) ;
		BoxCollider(dae::GameObject* pGO,int size);
		~BoxCollider() override;

		BoxCollider(const BoxCollider& other) = delete;
		BoxCollider(BoxCollider&& other) noexcept = delete;
		BoxCollider& operator=(const BoxCollider& other) = delete;
		BoxCollider& operator=(BoxCollider&& other) noexcept = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		bool IsOverlapping(const BoxCollider* collider, bool includeBorder = false) const;
		bool IsOverlapping(BoxCollider* collider, bool includeBorder, std::string tag ) const;
		bool IsOverlapping(BoxCollider* collider, std::string tag) const;

		SDL_Rect GetBoxCollider() const { return m_Collider; }
		void SetBoxCollider(SDL_Rect col) { m_Collider = col; }
	private:
		SDL_Rect m_Collider{};
};

