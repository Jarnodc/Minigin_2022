#pragma once
#include "UIButton.h"
class UILevelLoadingButton final: public UIButton
{
public:
	UILevelLoadingButton(dae::GameObject* pGO, const std::string& levelName,const SDL_Rect& srcRect, const SDL_Rect& dstRect, const std::string& path, bool hasPressedImage = true) ;
	~UILevelLoadingButton() override = default;

	UILevelLoadingButton(const UILevelLoadingButton& other) = delete;
	UILevelLoadingButton(UILevelLoadingButton&& other) noexcept = delete;
	UILevelLoadingButton& operator=(const UILevelLoadingButton& other) = delete;
	UILevelLoadingButton& operator=(UILevelLoadingButton&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void OnButtonDown() override;
	void OnButtonUp() override;
private:
	std::string m_LevelName;
};

