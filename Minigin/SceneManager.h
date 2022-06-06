#pragma once
#include <functional>
#include <map>

#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void LoadScene(const std::string& name);
		void SetSpawnLevelFunc(std::function<void(Scene&)> func,const std::string& LevelName);

		void Update() const;
		void FixedUpdate() const;
		void Render() const;

		dae::Scene& GetScene() const{ return *m_pActiveScene.get(); }
		int idxNextScene{ 1 };
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::shared_ptr<Scene> m_pActiveScene;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::map<std::string,std::function<void(Scene&)>> m_LevelFunc{};
	};
}
