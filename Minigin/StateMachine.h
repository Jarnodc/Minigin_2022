#pragma once
#include "State.h"
#include <map>

class StateMachine final
{
public:
	StateMachine() = default;
	~StateMachine();

	StateMachine(const StateMachine& other) = delete;
	StateMachine(StateMachine&& other) noexcept = delete;
	StateMachine& operator=(const StateMachine& other) = delete;
	StateMachine& operator=(StateMachine&& other) noexcept = delete;

	void Update() const;

	template<class s>
	s* ChangeState();
	void AddState(State* pState);
	template<class s>
	void RemoveState();
	template<class s>
	s* GetState();
	template<class s>
	bool IsState();
	template<class s>
	s* GetCurState() const {

		for (const auto& state : m_States)
		{
			if (typeid(*state) == typeid(*m_pCurState))
			{
				return dynamic_cast<s*>(state);
			}
		}
		return nullptr;
	}

private:
	State* m_pCurState{ nullptr };
	std::vector<State*> m_States{};
};

template<class s>
inline s* StateMachine::ChangeState()
{
	m_pCurState = GetState<s>();
	m_pCurState->Start();
	return dynamic_cast<s*>(m_pCurState);
}


template<class s>
inline void StateMachine::RemoveState()
{
	for (size_t i = 0; i < m_States.size(); ++i)
	{
		auto& state = m_States[i];
		if (typeid(*state) == typeid(s))
		{
			delete state;
			state = nullptr;
			m_States.erase(m_States.begin() + i);
			return;
		}
	}
}

template<class s>
s* StateMachine::GetState()
{
	for (const auto& state : m_States)
	{
		if(typeid(*state) == typeid(s))
		{
			return dynamic_cast<s*>(state);
		}
	}
	return nullptr;
}

template<class s>
inline bool StateMachine::IsState()
{
	if (!m_pCurState && m_States.empty())
		return false;
	if (!m_pCurState && !m_States.empty())
		m_pCurState = m_States.front();
	return typeid(*m_pCurState) == typeid(s);
}
