#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

std::vector<std::shared_ptr<SceneObject>> dae::Scene::GetObjects() const
{
	return m_Objects;
}

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;


void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void dae::Scene::Remove(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object));
}

void Scene::Update() const
{
	/*for(const auto& object : m_Objects)
	{
		object->Update();
	}*/
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Update();
	}
}
void Scene::FixedUpdate() const
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->FixedUpdate();
	}
	/*for(const auto& object : m_Objects)
	{
		object->FixedUpdate();
	}*/
}

void Scene::Render() const
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Render();
	}
	/*for (const auto& object : m_Objects)
	{
		object->Render();
	}*/
}

