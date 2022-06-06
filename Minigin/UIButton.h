#pragma once
#include "GameObject.h"
#include "Texture2D.h"

class UIButton : public Component
{
public:
	//Images has to be exactly the same size and near each other
	//the size of the srcRect is of 1 image (unpressed)
	UIButton(dae::GameObject* pGO,const SDL_Rect& srcRect, const SDL_Rect& dstRect,const std::string& path, bool hasPressedImage = true);
	~UIButton() override;

	UIButton(const UIButton& other) = delete;
	UIButton(UIButton&& other) noexcept = delete;
	UIButton& operator=(const UIButton& other) = delete;
	UIButton& operator=(UIButton&& other) noexcept = delete;

	virtual void Update() override{}
	virtual void FixedUpdate() override{}
	void Render() const override;

	void ButtonDown(const glm::vec2& mousePos);
	void ButtonUp(const glm::vec2& mousePos);

	virtual void OnButtonDown() = 0;
	virtual void OnButtonUp() = 0;

protected:
	virtual bool IsOverlapping(const glm::vec2& mousePos) const
	{
		return mousePos.x >= m_DstRect.x && mousePos.y >= m_DstRect.y && mousePos.x <= m_DstRect.x + m_DstRect.w && mousePos.y <= m_DstRect.y + m_DstRect.h; // including borders of rectangle
	}
	SDL_Rect m_SrcRect{};
	SDL_Rect m_DstRect{};

	const dae::Texture2D* m_pTexture{ nullptr };
private:
	bool m_HasPressedImage;
	bool m_HasChangedSrcRect{ false };

};

