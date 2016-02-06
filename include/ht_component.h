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

namespace Hatchit {

	namespace Game {

		class HT_API Component
		{
		public:
			/** Creates an Empty GameObject at 0,0,0
			*/
			virtual ~Component() { }

			/** Called when the gameobject is created to initialize all values
			*/
			virtual void VOnInit() = 0;
			/** Called when the gameobject is enabled
			* This happens when a scene has finished loading, or immediately after creation if the scene is already loaded.
			*/
			virtual void VOnEnabled() = 0;
			/** Called once per frame while the gameobject is enabled
			* Updates all components first, then all child gameobjects
			*/
			virtual void VOnUpdate() = 0;
			/** Called when the gameobject is disabled
			* Objects are always disabled before destroyed.
			* When a scene is destroyed, all gameobjects are disabled before any are destroyed.
			*/
			virtual void OnDisabled() = 0;
			/** Called when the gameobject is destroyed/deleted.
			* Objects are always disabled before destroyed.
			* When a scene is destroyed, all gameobjects are disabled before any are destroyed.
			*/
			virtual void VOnDestroy() = 0;
		};
	}
}
