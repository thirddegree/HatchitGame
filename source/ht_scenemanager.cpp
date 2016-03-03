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

		bool SceneManager::Initialize()
		{
			Core::DebugPrintF("Scene Manager Initialized (not implemented)\n");
			return false;
		}

		void SceneManager::Deinitialize()
		{
			Core::DebugPrintF("Scene Manager DeInitialized (not implemented)\n");
		}

		void SceneManager::Update()
		{
			SceneManager& _instance = SceneManager::instance();
			_instance.currentScene->Update();
			//Core::DebugPrintF("Scene Manager Update (not implemented)\n");
		}

		void SceneManager::Render()
		{
			SceneManager& _instance = SceneManager::instance();
			_instance.currentScene->Render();
			//Core::DebugPrintF("Scene Manager Render (not implemented)\n");
		}
	}
}
