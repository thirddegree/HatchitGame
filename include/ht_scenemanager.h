#pragma once
#include <ht_singleton.h>
#include <ht_scene.h>
#include <vector>

namespace Hatchit {

	namespace Game {

		class SceneManager : public Core::Singleton<SceneManager>
		{
		public:
			static bool Initialize();
			static void Deinitialize();
			static void Update();
			static void Render();

		private:
			static std::vector<Scene> scenes;
		};
	}
}