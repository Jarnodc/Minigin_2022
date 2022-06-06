#pragma once
#include "Component.h"
#include "Subject.h"
class SubjectComponent : public Component
{
public:
	Subject* GetSubject() const;

	SubjectComponent(const SubjectComponent& other) = delete;
	SubjectComponent(SubjectComponent&& other) noexcept = delete;
	SubjectComponent& operator=(const SubjectComponent& other) = delete;
	SubjectComponent& operator=(SubjectComponent&& other) noexcept = delete;
protected:
	explicit SubjectComponent(dae::GameObject* pGO);
	virtual ~SubjectComponent() override;
	
private:
	Subject* m_pSubject = nullptr;
};

