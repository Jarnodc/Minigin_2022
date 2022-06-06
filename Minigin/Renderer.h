#pragma once
#include <algorithm>
#include <chrono>
#include <functional>

#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	struct Transform2
	 {
		 float matrix[16] = {
			 1,0,0,0,
			 0,1,0,0,
			 0,0,1,0,
			 0,0,0,1 };
	 };

	 class GameObject3D
	 {
	 public:
		 Transform2 transform;
		 int ID;
	 };

	 class GameObject3Dalt
	 {
	 public:
		 Transform2* transform;
		 int ID;
	 };
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect, bool flipped) const;

		void RenderRectangle(const SDL_Rect& rect, SDL_Color color = {255,255,255,1 }) const;

		void RenderText(const std::string& text, const SDL_Rect& dstRect, const std::string& font = "Lingua.otf", int fontSize = 24, SDL_Color color = {255,255,255,1}) const;
		void RenderText(const std::string& text,  const SDL_Point& leftTop, const std::string& font = "Lingua.otf", int fontSize = 24, SDL_Color color = {255,255,255,1}) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	private:
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_clearColor{};

	};
}

