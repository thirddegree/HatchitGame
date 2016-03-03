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

#pragma once

#include <ht_platform.h>
#include <ht_singleton.h>
#include <ht_scene.h>
#include <vector>

namespace Hatchit {

	namespace Game {

		class HT_API SceneManager : public Core::Singleton<SceneManager>
		{
		public:
			static bool Initialize();
			static void Deinitialize();
			static void Update();
			static void Render();

		private:
			static std::vector<Scene> scenes;
			Scene* currentScene;
		};
	}
}
