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

        using JSON = nlohmann::json;

        /**
         * \brief Creates the scene manager.
         */
        SceneManager::SceneManager()
            : m_currentScene(nullptr)
        {
        }

        /**
         * \brief Destroys the scene manager.
         */
        SceneManager::~SceneManager()
        {
            m_currentScene = nullptr;
        }

        /**
         * \brief De-initializes the scene manager.
         */
        void SceneManager::Deinitialize()
        {
#if defined(DEBUG) || defined(_DEBUG)
            Core::DebugPrintF("Scene Manager DeInitialized (not implemented)\n");
#endif
        }

        /**
         * \brief Initializes the scene manager.
         */
        bool SceneManager::Initialize()
        {
            SceneManager& _instance = SceneManager::instance();

            const std::string folder = "../../../../HatchitGame/";
            const std::string sceneListFile = "SceneList.json";
            bool loaded = false;

            try
            {
                // Open the file
                File file;
                file.Open(folder + sceneListFile, FileMode::ReadText);

                // Prepare to read the file
                size_t fileSize = file.SizeBytes();
                if (fileSize == 0)
                {
                    DebugPrintF("WARNING: Scene list file is empty!\n");
                    return true;
                }
                std::string contents;
                contents.resize(fileSize);

                // Read the file
                file.Read(reinterpret_cast<BYTE*>(&contents[0]), contents.length());
                file.Close();

                // Try to parse the scene list
                JSON sceneList = JSON::parse(contents);

                // TODO - Change this when we finalize the scene
                DebugPrintF("Reading scene list...\n");
                for (const std::string& scenePath : sceneList)
                {
                    DebugPrintF("** Loading '%s'... ", scenePath);

                    File sceneFile;
                    sceneFile.Open(folder + scenePath, FileMode::ReadText);

                    _instance.m_scenes.emplace_back();
                    if (_instance.m_scenes.back().LoadFromFile(sceneFile))
                    {
                        DebugPrintF("Done!\n");
                    }
                    else
                    {
                        DebugPrintF("Failed!\n");
                    }

                    sceneFile.Close();
                }

                loaded = true;
            }
            catch (...)
            {
                DebugPrintF("Failed to load scene list!\n");
            }

            return loaded;
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
                _instance.m_currentScene = nullptr;
            }

            // Scan for the scene with the given name
            for (Scene& scene : _instance.m_scenes)
            {
                if (scene.Name() == sceneName)
                {
                    _instance.m_currentScene = &scene;
                    break;
                }
            }

            // If we've found the scene, load it from the cache
            if (_instance.m_currentScene)
            {
                return _instance.m_currentScene->LoadFromCache();
            }
            return false;
        }

        /**
         * \brief Loads a scene asynchronously.
         *
         * Begins loading the specified scene while the current scene continues to run.
         * When the scene is finished loading, unloads the current scene.
         * If the scene does not exist in the list of scenes, an error is thrown.
         */
        void SceneManager::LoadSceneAsync(const std::string& sceneName)
        {
#if defined(DEBUG) || defined(_DEBUG)
            Core::DebugPrintF("TODO - SceneManager::LoadSceneAsync (add callback params)\n");
#endif
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
