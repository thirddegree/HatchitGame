#include "ht_scene.h"


namespace Hatchit {

	namespace Game {

		Hatchit::Game::Scene::Scene()
		{

		}

		Hatchit::Game::Scene::~Scene()
		{

		}

		void Scene::Update()
		{
			for (int i = 0; i < gameObjects.size(); i++)
			{
				gameObjects[i].Update();
			}
		}

		void Scene::Render()
		{
			for (int i = 0; i < gameObjects.size(); i++)
			{
				gameObjects[i].Update();
			}
		}
	}
}
