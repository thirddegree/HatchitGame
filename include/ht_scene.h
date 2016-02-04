#pragma once
#include <ht_gameobject.h>
#include <vector>

namespace Hatchit {

	namespace Game {

		class Scene
		{
		public:
			Scene();
			~Scene();

			void Update();
			void Render();

		private:
			std::vector<GameObject> gameObjects;
		};
	}
}