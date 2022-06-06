#include "MiniginPCH.h"
#include "StateMachine.h"

StateMachine::~StateMachine()
{
	for (auto& state : m_States)
	{
		delete state;
		state = nullptr;
	}
	m_States.clear();
}

void StateMachine::AddState(State* pState)
{
	m_States.push_back(pState);
}
void StateMachine::Update() const
{
	if(m_pCurState)
		m_pCurState->Execute();
}

