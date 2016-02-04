#pragma once

namespace Hatchit {

	namespace Game {

		class Component
		{
		public:
			/** Creates an Empty GameObject at 0,0,0
			*/
			Component();
			~Component();

			/** Called when the gameobject is created to initialize all values
			*/
			void OnInit();
			/** Called when the gameobject is enabled
			* This happens when a scene has finished loading, or immediately after creation if the scene is already loaded.
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
		};
	}
}