#include "MiniginPCH.h"
#include "MovementComponent.h"

#include "BoxCollider.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "RigidBody.h"
#include "TimerInfo.h"

void MovementComponent::Move(glm::vec3 moveVec)
{
	const auto rigidBody{ GetGameObject()->GetComponent<RigidBody>() };
	const auto velocity = moveVec * dae::TimerInfo::GetInstance().deltaTime * rigidBody->GetSpeed();

	if (velocity.x > 0 && !CanMoveTo(EDirection::Right))//CanMoveLeft
	{
		moveVec.x = 0;
	}
	else if (velocity.x < 0 && !CanMoveTo(EDirection::Left))//CanMoveRight
	{
		moveVec.x = 0;
	}
	if (velocity.y > 0 && !CanMoveTo(EDirection::Down))//CanMoveDown
	{
		moveVec.y = 0;
	}
	else if(velocity.y < 0 && !CanMoveTo(EDirection::Up))//CanMoveUp
	{
		moveVec.y = 0;
	}
	rigidBody->Move(moveVec);
}

bool MovementComponent::CanMoveTo(EDirection dir) const
{
	const auto rigidBody{ GetGameObject()->GetComponent<RigidBody>() };
	auto velocity = dae::TimerInfo::GetInstance().deltaTime * rigidBody->GetSpeed();
	const auto curPos = GetGameObject()->GetLocalPosition();
	const auto boxCollider = GetGameObject()->GetComponent<BoxCollider>();
	auto rect = boxCollider->GetBoxCollider();
	const auto width{ rect.w }, left{ rect.x };
	const auto height{ rect.h }, bottom{ rect.y };
	switch(dir)
	{
	case EDirection::Up:
		{
			velocity *= glm::vec3{0, -1, 0};
			rect.y += static_cast<int>(velocity.y) -1;
			boxCollider->SetBoxCollider(rect);
			if (!PhysicsManager::GetInstance().IsOverlapping(boxCollider, std::string("Ladder")))
			{
				rect.h = height;
				rect.y = bottom;
				boxCollider->SetBoxCollider(rect);
				return false;
			}
			const auto ladder = PhysicsManager::GetInstance().GetOverlappers(boxCollider, std::string("Ladder"));
			const auto bc{ ladder.front()->GetBoxCollider() };
			if (abs((bc.x + (bc.w / 2.f)) - (curPos.x + (rect.w / 2.f))) > 2)
			{
				rect.h = height;
				rect.y = bottom;
				boxCollider->SetBoxCollider(rect);
				return false;
			}
			rect.h = height;
			rect.y = bottom;
			boxCollider->SetBoxCollider(rect);
		}
		break;
	case EDirection::Down:
		{
			velocity *= glm::vec3{ 0, 1, 0 };
			rect.y += static_cast<int>(velocity.y) + rect.h;
			boxCollider->SetBoxCollider(rect);
			if (!PhysicsManager::GetInstance().IsOverlapping(boxCollider, std::string("Ladder")))
			{
				rect.h = height;
				rect.y = bottom;
				boxCollider->SetBoxCollider(rect);
				return false;
			}
			const auto ladder = PhysicsManager::GetInstance().GetOverlappers(boxCollider, std::string("Ladder"));
			const auto bc{ ladder.front()->GetBoxCollider() };
			if (abs((bc.x + (bc.w / 2.f)) - (curPos.x + (rect.w / 2.f))) > 2)
			{
				rect.h = height;
				rect.y = bottom;
				boxCollider->SetBoxCollider(rect);
				return false;
			}
			rect.h = height;
			rect.y = bottom;
			boxCollider->SetBoxCollider(rect);
		}
		break;
	case EDirection::Left:
		{
			velocity *= glm::vec3{  -1,0, 0 };
			rect.w = 2;
			rect.h = 2;
			rect.y += height - rect.h + 1;
			rect.x += (static_cast<int>(velocity.x) + 1);
			boxCollider->SetBoxCollider(rect);
			if (!PhysicsManager::GetInstance().IsOverlapping(boxCollider, std::string("Ground")))
			{
				rect.x = left;
				rect.w = width;
				rect.y = bottom;
				rect.h = height;
				boxCollider->SetBoxCollider(rect);
				return false;
			}
			rect.x = left;
			rect.w = width;
			rect.h = height;
			rect.y = bottom;
			boxCollider->SetBoxCollider(rect);
		}
		break;
	case EDirection::Right:
		{
			velocity *= glm::vec3{  1, 0,0 };
			rect.w = 2;
			rect.h = 2;
			rect.y += height - rect.h + 1;
			rect.x += static_cast<int>(width - rect.w + velocity.x + 1);
			boxCollider->SetBoxCollider(rect);
			if (!PhysicsManager::GetInstance().IsOverlapping(boxCollider, std::string("Ground")))
			{
				rect.x = left;
				rect.w = width;
				rect.h = height;
				rect.y = bottom;
				boxCollider->SetBoxCollider(rect);
				return false;
			}
			rect.x = left;
			rect.w = width;
			rect.h = height;
			rect.y = bottom;
			boxCollider->SetBoxCollider(rect);
		}
		break;
	case EDirection::Horizontal:
		return CanMoveTo(EDirection::Left) || CanMoveTo(EDirection::Right);
		break;
	case EDirection::Vertical:
		return CanMoveTo(EDirection::Down) || CanMoveTo(EDirection::Up);
		break;
	}
	return true;
}
