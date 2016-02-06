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
#include <ht_component.h>
#include <vector>

namespace Hatchit {

	namespace Game {

		class HT_API GameObject
		{
		public:
			/**
             * Creates an Empty GameObject at 0,0,0
			 */
			GameObject();
			
            ~GameObject();


			/**
             * Called when the gameobject is created to initialize all values
			 */
			void OnInit();


			/** Called when the gameobject is enabled
			*   This happens when a scene has finished loading, or immediately after creation if the scene is already loaded.
			*/
			void OnEnabled();


			/** Called once per frame while the gameobject is enabled
			* Updates all components first, then all child gameobjects
			*/
			void Update();

			/** Called when the gameobject is disabled
			* Objects are always disabled before destroyed.
			* When a scene is destroyed, all gameobjects are disabled before any are destroyed.
			*/
			void OnDisabled();


			/** Called when the gameobject is destroyed/deleted.
			* Objects are always disabled before destroyed.
			* When a scene is destroyed, all gameobjects are disabled before any are destroyed.
			*/
			void OnDestroy();


		private:
			std::vector<Component*> m_components;
		};
	}
}
