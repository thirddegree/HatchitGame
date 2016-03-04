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

#include "ht_scenemanager.h"
#include "ht_debug.h"

namespace Hatchit {

	namespace Game {

		using namespace Core;
		using json = nlohmann::json;

		bool SceneManager::Initialize()
		{
			//Load list of scenes
			std::vector<std::string> scenePaths = { "" };
			
			
			
			//Load text file for each scene
			for (auto const path : scenePaths)
			{
				json data = json::parse("{}");
				scenes.emplace_back(data);
			}

			//Load first scene
			if (scenes.size == 0)
				return false;

			scenes[0].Load();

			return true;
		}

		void SceneManager::Deinitialize()
		{
			Core::DebugPrintF("Scene Manager DeInitialized (not implemented)\n");
		}

		void SceneManager::Update()
		{
			SceneManager& _instance = SceneManager::instance();
			_instance.currentScene->Update();
		}

		void SceneManager::Render()
		{
			SceneManager& _instance = SceneManager::instance();
			_instance.currentScene->Render();
		}
		
		void SceneManager::LoadScene(std::string sceneName)
		{
			UnloadScene();

			SceneManager& _instance = SceneManager::instance();

			for (auto const scene : scenes)
			{
				if (_instance.currentScene->name == sceneName)
				{
					_instance.currentScene = (Scene*) &scene;
					break;
				}
			}

			_instance.currentScene->Load();
		}

		void SceneManager::LoadSceneAsync(std::string sceneName)
		{
			Core::DebugPrintF("Scene Manager LoadSceneAsync (not implemented)\n");
		}
		
		void SceneManager::UnloadScene()
		{
			Core::DebugPrintF("Scene Manager UnloadScene (not implemented)\n");
		}
	}
}
