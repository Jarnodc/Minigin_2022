#pragma once
#include "Component.h"
#include "Transform.h"
#include "Font.h"
#include "Texture2D.h"

namespace dae
{
	class TextComponent final: public Component
	{
	public:
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font>& font);
		void SetColor(const SDL_Color& color);
		void SetPosition(float x, float y);
		
		explicit TextComponent(dae::GameObject* pGO, const std::string& text, const std::shared_ptr<Font>& font);
		explicit TextComponent(dae::GameObject* pGO);
		~TextComponent() override;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	protected:
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		SDL_Color m_Color = { 255,255,255 };
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}
