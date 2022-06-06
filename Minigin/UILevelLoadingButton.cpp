#include "MiniginPCH.h"
#include "UILevelLoadingButton.h"

#include "Renderer.h"
#include "SceneManager.h"

UILevelLoadingButton::UILevelLoadingButton(dae::GameObject* pGO, const std::string& levelName, const SDL_Rect& srcRect, const SDL_Rect& dstRect, const std::string& path, bool hasPressedImage)
	:UIButton(pGO,srcRect,dstRect,path,hasPressedImage)
	,m_LevelName(levelName)
{
}

void UILevelLoadingButton::Update()
{
}

void UILevelLoadingButton::FixedUpdate()
{
}

void UILevelLoadingButton::Render() const
{
	UIButton::Render();
	const auto offset{ m_DstRect.w / 10 };
	const SDL_Rect offsetRect{ m_DstRect.x + offset,m_DstRect.y + offset,m_DstRect.w - 2 * offset, m_DstRect.h - 2 * offset };
	dae::Renderer::GetInstance().RenderText(m_LevelName, offsetRect);
}

void UILevelLoadingButton::OnButtonDown()
{
}

void UILevelLoadingButton::OnButtonUp()
{
	dae::SceneManager::GetInstance().LoadScene(m_LevelName);
}
