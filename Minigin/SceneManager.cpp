#include "MiniginPCH.h"
#include "SceneManager.h"

#include <functional>

#include "Scene.h"

void dae::SceneManager::Update() const
{
	//for(auto& scene : m_Scenes)
	if (m_pActiveScene)
	{
		m_pActiveScene->Update();
	}
}

void dae::SceneManager::FixedUpdate() const
{
	//for (auto& scene : m_Scenes)
	if (m_pActiveScene)
	{
		m_pActiveScene->FixedUpdate();
	}
}

void dae::SceneManager::Render() const
{
	//for (const auto& scene : m_Scenes)
	if(m_pActiveScene)
	{
		m_pActiveScene->Render();
	}
}

void dae::SceneManager::LoadScene(const std::string& name)
{
	if(!m_LevelFunc.contains(name))
		return;
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_LevelFunc[name](*scene);
	//m_Scenes.emplace_back(scene);
	m_pActiveScene = scene;
}

void dae::SceneManager::SetSpawnLevelFunc(std::function<void(Scene&)> func, const std::string& LevelName)
{
	m_LevelFunc[LevelName] = func;
}
