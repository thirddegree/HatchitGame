/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/



#include "ht_scene.h"


namespace Hatchit {

	namespace Game {
		using json = nlohmann::json;
		Scene::Scene()
		{

		}

		Scene::Scene(json data)
		{
			sceneDescription = data;
			name = data["Name"].get<std::string>();
		}

		Scene::~Scene()
		{

		}

		void Scene::Update()
		{
			for (size_t i = 0; i < gameObjects.size(); i++)
			{
				gameObjects[i].Update();
			}
		}

		void Scene::Render()
		{
			for (size_t i = 0; i < gameObjects.size(); i++)
			{
				gameObjects[i].GetTransform()->UpdateWorldMatrix();
			}
		}

		void Scene::Load()
		{
			for (json::iterator iter = sceneDescription["GameObjects"].begin(); iter != sceneDescription["GameObjects"].end(); ++iter)
			{
				json val = iter.value();
				std::string guid = val["GUID"];
				GameObject* gameObject = CreateGameObject();
				Transform* transform = gameObject->GetTransform();
			}


		}

		GameObject* Scene::CreateGameObject()
		{
			gameObjects.emplace_back();
			return (GameObject*) &gameObjects.back();
		}

		GameObject* Scene::CreateGameObject(uint8_t uuid[])
		{
			gameObjects.emplace_back(uuid);
			return (GameObject*)&gameObjects.back();
		}

	}
}
