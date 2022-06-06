#include "MiniginPCH.h"
#include "SubjectComponent.h"

Subject* SubjectComponent::GetSubject() const
{
	return m_pSubject;
}

SubjectComponent::SubjectComponent(dae::GameObject* pGO)
	:Component(pGO)
	,m_pSubject(new Subject())
{
}

SubjectComponent::~SubjectComponent()
{
	delete m_pSubject;
	m_pSubject = nullptr;
}
