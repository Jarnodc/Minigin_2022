#pragma once
#include "EEvent.h"
#include "GameObject.h"

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Notify(const dae::GameObject& pObject, EEvent event) = 0;
};

