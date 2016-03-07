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
#include <ht_gameobject.h>
#include <json.hpp>
#include <vector>
#include <ht_debug.h>

#ifdef HT_SYS_LINUX
	#include <cstdlib>
#endif

namespace Hatchit {

	namespace Game {

		class HT_API Scene
		{
		public:
			Scene();
			Scene(nlohmann::json data);
			~Scene();

			void Update();
			void Render();

			/**
			 * Loads in assets and constructs GameObjects.
			 */
			void Load();

			/**
			 * Creates GameObject and adds it to internal list.
			 */
			GameObject* CreateGameObject();

			std::string name;

		private:
			GameObject* CreateGameObject(uint8_t uuid[]);

			std::vector<GameObject> gameObjects;
			nlohmann::json sceneDescription;

		};
	}
}
