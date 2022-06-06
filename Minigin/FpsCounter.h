#pragma once
#include "GameObject.h"
#include "TextComponent.h"
namespace dae {
    class FpsCounter final: public Component
    {
    public: 
        FpsCounter(dae::GameObject* pGO) :Component(pGO), m_Frames{m_SecPerUpdate}{}
        ~FpsCounter() override;

        FpsCounter(const FpsCounter& other) = delete;
        FpsCounter(FpsCounter&& other) = delete;
        FpsCounter& operator=(const FpsCounter& other) = delete;
        FpsCounter& operator=(FpsCounter&& other) = delete;

        void Update() override;
        void FixedUpdate() override;
        void Render() const override;
    private:
        float m_SecPerUpdate{ .5f };
        float m_Frames{  };
    };
}

