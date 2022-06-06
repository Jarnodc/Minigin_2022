#include "MiniginPCH.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::Texture::Texture(dae::GameObject* go)
	:Component(go)
	,m_Texture{nullptr}, m_Transform(go)
{
}

dae::Texture::~Texture()
{
}

void dae::Texture::Update()
{
	
}
void dae::Texture::FixedUpdate()
{
}

void dae::Texture::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = m_Transform.GetLocalPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::Texture::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
void dae::Texture::SetPosition(const float x, const float y)
{
	m_Transform.SetLocalPosition(x, y, 0.0f);
}
