#include "MiniginPCH.h"
#include "SpriteComponent.h"

#include "Texture2D.h"
#include "TimerInfo.h"

SpriteComponent::SpriteComponent(dae::GameObject* pGO, const std::string& path, int rows, int cols, int x, int y, float animationSpeed)
	:Component(pGO)
	,m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(path))
	,m_AnimationTime(animationSpeed)
{
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &m_Width, &m_Height);
	m_SpritePart.Cols = cols;
	m_SpritePart.Rows = rows;
	m_SpritePart.StartPos = { x,y };
	m_SpritePart.SrcRect.x = x;
	m_SpritePart.SrcRect.y = y;
	m_SpritePart.SrcRect.w = m_Width / cols;
	m_SpritePart.SrcRect.h = m_Height / rows;
	m_DstRect.x = 0;
	m_DstRect.y = 0;
	m_DstRect.w = m_Width / cols;
	m_DstRect.h = m_Height / rows;
}

SpriteComponent::SpriteComponent(dae::GameObject* pGO, const std::string& path, int rows, int cols, float animationSpeed)
	:Component(pGO)
	, m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(path))
	, m_AnimationTime(animationSpeed)
{
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &m_Width, &m_Height);
	m_SpritePart.Cols = cols;
	m_SpritePart.Rows = rows;
	m_SpritePart.StartPos = { 0,0 };
	m_SpritePart.SrcRect.x = 0;
	m_SpritePart.SrcRect.y = 0;
	m_SpritePart.SrcRect.w = m_Width / cols;
	m_SpritePart.SrcRect.h = m_Height / rows;
	m_DstRect.x = 0;
	m_DstRect.y = 0;
	m_DstRect.w = m_Width / cols;
	m_DstRect.h = m_Height / rows;
}

SpriteComponent::SpriteComponent(dae::GameObject* pGO, const std::string& path, SpritePart sp, float animationSpeed)
	:Component(pGO)
	, m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(path))
	, m_AnimationTime(animationSpeed)
	, m_SpritePart{sp}
{
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &m_Width, &m_Height);
	m_DstRect.x = 0;
	m_DstRect.y = 0;
	m_DstRect.w = sp.SrcRect.w;
	m_DstRect.h = sp.SrcRect.h;
}

SpriteComponent::SpriteComponent(dae::GameObject* pGO, const std::string& path, SpritePart sp)
	:Component(pGO)
	, m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(path))
	, m_SpritePart{ sp }
{
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &m_Width, &m_Height);
	m_DstRect.x = 0;
	m_DstRect.y = 0;
	m_DstRect.w = sp.SrcRect.w;
	m_DstRect.h = sp.SrcRect.h;
}

SpriteComponent::SpriteComponent(dae::GameObject* pGO, const std::string& path, SpritePart sp, glm::vec2 scale)
	:Component(pGO)
	, m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(path))
	, m_SpritePart{ sp }
{
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &m_Width, &m_Height);
	m_DstRect.x = 0;
	m_DstRect.y = 0;
	m_DstRect.w = static_cast<int>(sp.SrcRect.w * scale.x);
	m_DstRect.h = static_cast<int>(sp.SrcRect.h * scale.y);
}

SpriteComponent::SpriteComponent(dae::GameObject* pGO, const std::string& path, SpritePart sp, float animationSpeed, SDL_Rect dstRect)
	:SpriteComponent(pGO,path,sp,animationSpeed)
{
	m_DstRect = dstRect;
}

SpriteComponent::SpriteComponent(dae::GameObject* pGO, const std::string& path, int rows, int cols, int x, int y, int width, int height, float animationSpeed)
	:Component(pGO)
	,m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(path))
	, m_AnimationTime(animationSpeed)
{
	m_SpritePart.Cols = cols;
	m_SpritePart.Rows = rows;
	m_SpritePart.StartPos = {x,y};
	m_SpritePart.SrcRect.x = x;
	m_SpritePart.SrcRect.y = y;
	m_SpritePart.SrcRect.w = width / cols;
	m_SpritePart.SrcRect.h = height / rows;
	m_DstRect.x = 0;
	m_DstRect.y = 0;
	m_DstRect.w = width / cols;
	m_DstRect.h = height / rows;
}

SpriteComponent::SpriteComponent(dae::GameObject* pGO, const std::string& path, int rows, int cols, SDL_Point leftTop, int width, int height, float animationSpeed)
	:SpriteComponent(pGO, path, rows, cols, leftTop.x, leftTop.y, width, height, animationSpeed)
{
}

SpriteComponent::SpriteComponent(dae::GameObject* pGO, const std::string& path, int rows, int cols, SDL_Rect srcRect, float animationSpeed)
	:SpriteComponent(pGO,path,rows,cols,srcRect.x,srcRect.y,srcRect.w,srcRect.h,animationSpeed)
{
}

void SpriteComponent::Update()
{
	m_curTimer += dae::TimerInfo::GetInstance().deltaTime;
	if(m_curTimer >= m_AnimationTime)
	{
		MoveToNextFrame();
		m_curTimer -= m_AnimationTime;
	}
}

void SpriteComponent::FixedUpdate()
{
}

void SpriteComponent::Render() const
{
	const auto pos = GetGameObject()->GetLocalPosition();
	const SDL_Rect tempDstRect{ static_cast<int>(m_DstRect.x + pos.x), static_cast<int>(m_DstRect.y + pos.y), m_DstRect.w,m_DstRect.h };
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, m_SpritePart.SrcRect, tempDstRect, m_Flip);
}

void SpriteComponent::SetFlip(bool flip)
{
	m_Flip = flip;
}

void SpriteComponent::MoveToNextFrame()
{
	if(m_CurCol != m_SpritePart.Cols)
	{
		++m_CurCol;
	}
	else
	{
		m_CurCol = 1;
		if(m_CurRow != m_SpritePart.Rows)
		{
			++m_CurRow;
		}
		else
		{
			m_CurRow = 1;
			m_ReachedEnd = true;
		}
		m_SpritePart.SrcRect.y = (m_CurRow - 1) *( m_SpritePart.SrcRect.h  + m_SpritePart.OffSetVer) + m_SpritePart.StartPos.y;
	}
	m_SpritePart.SrcRect.x = (m_CurCol - 1) * (m_SpritePart.SrcRect.w  + m_SpritePart.OffSetHor) + m_SpritePart.StartPos.x;
}

