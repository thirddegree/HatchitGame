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

#include <ht_scenemanager_singleton.h>
#include <ht_path_singleton.h>
#include <ht_debug.h>

namespace Hatchit {

    namespace Game {
        using namespace Core;
        using namespace Resource;

        std::string SceneManager::SCENE_LIST = "scenelist.json";

        /**
         * \brief De-initializes the scene manager.
         */
        void SceneManager::Deinitialize()
        {
            SceneManager& _instance = SceneManager::instance();

            if (_instance.m_currentScene)
            {
                _instance.m_currentScene->Unload();
                delete _instance.m_currentScene;
            }
        }

        /**
         * \brief Initializes the scene manager.
         */
        bool SceneManager::Initialize()
        {
            SceneManager& _instance = SceneManager::instance();

            // Validate that we were able to acquire a handle to the JSON scene list.
            SceneHandle sceneListHandle = Resource::Scene::GetHandleFromFileName(SceneManager::SCENE_LIST);
            if (!sceneListHandle.IsValid())
            {
                HT_DEBUG_PRINTF("Failed to acquire handle scene list located in %s!\n", SceneManager::SCENE_LIST);
                return false;
            }

            // Iterate through every JSON scene file listed.
            const JSON& sceneDescription = sceneListHandle->GetSceneDescription();
            for (const std::string& sceneFile : sceneDescription)
            {
                // Validate that we were able to acquire a handle to the JSON scene file.
                SceneHandle sceneHandle = Resource::Scene::GetHandleFromFileName(sceneFile);
                if (!sceneHandle.IsValid())
                {
                    HT_DEBUG_PRINTF("Failed to acquire handle to scene located in %s!\n", sceneFile);
                    continue;
                }

                _instance.m_sceneHandles.insert(std::make_pair(sceneFile, sceneHandle));
            }

            return true;
        }

        /**
         * \brief Loads the given scene.
         *
         * Unloads the current scene and loads in the specified scene.
         * If the scene does not exist in the list of scenes, an error is thrown.
         */
        bool SceneManager::LoadScene(const std::string& sceneName)
        {
            SceneManager& _instance = SceneManager::instance();

            // Unload the current scene
            if (_instance.m_currentScene)
            {
                _instance.m_currentScene->Unload();
                delete _instance.m_currentScene;
            }

            // Locate the handle to the next scene.
            auto sceneIterator = _instance.m_sceneHandles.find(sceneName);
            if (sceneIterator == _instance.m_sceneHandles.cend())
            {
                HT_DEBUG_PRINTF("Failed to locate requested Scene: %s!\n", sceneName);
                return false;
            }

            // Validate the handle to the next Scene.
            SceneHandle sceneHandle = sceneIterator->second;
            if (!sceneHandle.IsValid())
            {
                HT_DEBUG_PRINTF("Invalid Scene handle: %s!\n", sceneName);
                return false;
            }

            // Load the Scene from the provided SceneHandle.
            _instance.m_currentScene = new Scene();
            if (!_instance.m_currentScene->LoadFromHandle(sceneHandle))
            {
                HT_DEBUG_PRINTF("Failed to load Scene from handle: %s!\n", sceneName);
                return false;
            }

            // Initialize the Scene.
            _instance.m_currentScene->Init();
            
            return true;
        }
        
        /**
         * \brief Updates the scene manager.
         */
        void SceneManager::Update()
        {
            SceneManager& _instance = SceneManager::instance();

            if (_instance.m_currentScene)
            {
                _instance.m_currentScene->Update();
                _instance.m_currentScene->Render();
            }
        }

    }
}
