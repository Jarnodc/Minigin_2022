#pragma once
#include "GameObject.h"
#include "Observer.h"
class Subject
{
public:
	Subject() = default;
	~Subject() = default;

	Subject(const Subject& other) = delete;
	Subject(Subject&& other) noexcept = delete;
	Subject& operator=(const Subject& other) = delete;
	Subject& operator=(Subject&& other) noexcept = delete;

	void AddObserver(Observer* pObserver);
	void RemoveObserver(Observer* pObserver);

	void Notify(const dae::GameObject& gameObject, EEvent event) const;
protected:
private:
	std::vector<Observer*> m_pObservers{};
};

