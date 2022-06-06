#pragma once
#include "Observer.h"
#include "Renderer.h"

class SpriteComponent : public Component
{
public:
	struct SpritePart
	{
		SpritePart() = default;
		SpritePart(int cols,int rows,SDL_Rect srcRect, int offSetHor,int offSetVer, SDL_Point startPos)
			:Cols{ cols }, Rows{ rows }, SrcRect{ srcRect }, OffSetHor{ offSetHor }, OffSetVer{ offSetVer }, StartPos{ startPos }{}

		SpritePart(SDL_Rect srcRect, int offSetHor = 0, int offSetVer = 0)
			:Cols{ 1 }, Rows{ 1 }, SrcRect{ srcRect }, OffSetHor{ offSetHor }, OffSetVer{ offSetVer }, StartPos{ srcRect.x,srcRect.y }{}

		SpritePart(SDL_Point startPos, int size, int offSetHor = 0, int offSetVer = 0)
			:Cols{ 1 }, Rows{ 1 }, SrcRect{ startPos.x,startPos.y,size,size }, OffSetHor{ offSetHor }, OffSetVer{ offSetVer }, StartPos{ startPos }{}

		SpritePart(int cols, int rows, SDL_Point startPos, int size, int offSetHor = 0, int offSetVer = 0)
			:Cols{ cols }, Rows{ rows }, SrcRect{ startPos.x,startPos.y,size,size }, OffSetHor{ offSetHor }, OffSetVer{ offSetVer }, StartPos{ startPos }{}

		SpritePart(int cols, int rows, SDL_Rect srcRect, int offSetHor = 0, int offSetVer = 0)
			:Cols{ cols }, Rows{ rows }, SrcRect{ srcRect }, OffSetHor{ offSetHor }, OffSetVer{ offSetVer }, StartPos{ srcRect.x,srcRect.y }{}

		int Cols{ 1 };
		int Rows{ 1 };
		SDL_Rect SrcRect{ 0,0 };
		int OffSetHor{ 0 }, OffSetVer{ 0 };
		SDL_Point StartPos{};
		bool operator==(const SpritePart& other) const
		{
			return Cols == other.Cols && Rows == other.Rows && OffSetHor == other.OffSetHor && OffSetVer == other.OffSetVer && StartPos.x == other.StartPos.x && StartPos.y == other.StartPos.y && SrcRect.x == other.SrcRect.x && SrcRect.y == other.SrcRect.y && SrcRect.w == other.SrcRect.w && SrcRect.h == other.SrcRect.h;
		}
	};
	SpriteComponent(dae::GameObject* pGO, const std::string& path, int rows, int cols, int x, int y, float animationSpeed);
	SpriteComponent(dae::GameObject* pGO, const std::string& path, int rows, int cols, float animationSpeed);
	SpriteComponent(dae::GameObject* pGO, const std::string& path, SpritePart sp, float animationSpeed);
	SpriteComponent(dae::GameObject* pGO, const std::string& path, SpritePart sp);
	SpriteComponent(dae::GameObject* pGO, const std::string& path, SpritePart sp, glm::vec2 scale);
	SpriteComponent(dae::GameObject* pGO, const std::string& path, SpritePart sp, float animationSpeed,SDL_Rect dstRect);
	SpriteComponent(dae::GameObject* pGO, const std::string& path, int rows, int cols, int x, int y, int width, int height, float animationSpeed);
	SpriteComponent(dae::GameObject* pGO, const std::string& path, int rows, int cols, SDL_Point leftTop, int width, int height, float animationSpeed);
	SpriteComponent(dae::GameObject* pGO, const std::string& path, int rows, int cols, SDL_Rect srcRect, float animationSpeed);
	~SpriteComponent() override = default;

	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) noexcept = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void SetFlip(bool flip);

	bool HasReachedEnd()const
	{
		return m_ReachedEnd;
	}

	void ChangeState(const SpritePart& sp)
	{
		if (m_SpritePart == sp)
			return;
		m_SpritePart = sp;
		m_CurCol = m_CurRow = 1;
		m_curTimer = 0;
	}
	void ChangePosition(const SDL_Point& pos)
	{
		m_SpritePart.SrcRect.x = pos.x;
		m_SpritePart.SrcRect.y = pos.y;
		m_SpritePart.StartPos =  pos;
		m_CurCol = m_CurRow = 1;
		m_curTimer = 0;
	}
	void ResetComponent() override { m_Flip = false; m_ReachedEnd = false; m_curTimer = 0;	m_CurCol = m_CurRow = 1; }
	SpritePart GetSpritePart()const { return m_SpritePart; }
private:
	void MoveToNextFrame();
	const dae::Texture2D* m_pTexture{ nullptr };
	SDL_Rect m_DstRect{};
	SpritePart m_SpritePart{};
	int m_Width{}, m_Height{}, m_CurCol{1},m_CurRow{1};
	float m_AnimationTime{ 1 };
	float m_curTimer{ 0 };
	bool m_Flip{ false };
	bool m_ReachedEnd{ false };
};

