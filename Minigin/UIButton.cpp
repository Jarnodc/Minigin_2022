#include "MiniginPCH.h"
#include "UIButton.h"

#include "UIManager.h"

UIButton::UIButton(dae::GameObject* pGO, const SDL_Rect& srcRect, const SDL_Rect& dstRect, const std::string& path, bool hasPressedImage)
	:Component(pGO)
	,m_SrcRect(srcRect)
	,m_DstRect(dstRect)
	,m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(path))
	,m_HasPressedImage(hasPressedImage)
{
	UIManager::GetInstance().AddButton(this);
}

UIButton::~UIButton()
{
	UIManager::GetInstance().RemoveButton(this);
}

void UIButton::Render() const
{
	const SDL_Rect tempDstRect{ static_cast<int>(m_DstRect.x), static_cast<int>(m_DstRect.y), m_DstRect.w,m_DstRect.h };
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, m_SrcRect, tempDstRect,false);
}

void UIButton::ButtonDown(const glm::vec2& mousePos)
{
	if (!IsOverlapping(mousePos))
		return;

	if(m_HasPressedImage)
	{
		m_SrcRect.x += m_SrcRect.w;
		m_HasChangedSrcRect = true;
	}

	OnButtonDown();
}

void UIButton::ButtonUp(const glm::vec2& mousePos)
{
	if (m_HasPressedImage && m_HasChangedSrcRect)
	{
		m_SrcRect.x -= m_SrcRect.w;
	}

	if (!IsOverlapping(mousePos))
		return;

	OnButtonUp();
}
