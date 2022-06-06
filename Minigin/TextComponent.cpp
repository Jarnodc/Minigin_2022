#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(dae::GameObject* pGO, const std::string& text, const std::shared_ptr<Font>& font)
	:Component(pGO)
	, m_NeedsUpdate(true), m_Text(text), m_Font(font), m_TextTexture(nullptr), m_Color({ 255,255,255 })
	,m_Transform(pGO)
{
}

dae::TextComponent::TextComponent(dae::GameObject* pGO)
	: Component(pGO)
	, m_NeedsUpdate(true), m_Text(" "), m_Font(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36)), m_TextTexture(nullptr), m_Color({ 255,255,255 })
	, m_Transform(pGO)
{
}

dae::TextComponent::~TextComponent()
{
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr) 
		{
			return;
			//throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			return;
			//throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}
void dae::TextComponent::FixedUpdate()
{

}

void dae::TextComponent::Render() const
{
	if (m_TextTexture != nullptr)
	{
		const auto& pos = m_Transform.GetLocalPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetFont(const std::shared_ptr<Font>& font)
{
	m_Font = font;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
}

void dae::TextComponent::SetPosition(const float x, const float y)
{
	m_Transform.SetLocalPosition(x, y, 0.0f);
}


