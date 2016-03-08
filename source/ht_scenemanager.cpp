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
        using json = nlohmann::json;

        bool SceneManager::Initialize()
        {
            SceneManager& _instance = SceneManager::instance();
            std::string path = "C:\\Users\\MagicUser\\Desktop\\Hatchit\\HatchitGame\\";
            //load list of scenes
            json scenePaths = LoadJSON(path + "scenelist.json");			

            //Load json for each scene
            for (std::string const sceneFile : scenePaths["scenes"])
            {
                std::string filePath = path + sceneFile;
                Core::File file;
                file.Open(filePath, Core::FileMode::ReadText);

                _instance.scenes.emplace_back();
                _instance.scenes.back().LoadFromFile(file);
            }


            //Load first scene
            if (_instance.scenes.size() == 0)
                return false;

            Core::DebugPrintF("SceneManager loaded scenes successfully.");

            return true;
        }

        void SceneManager::Deinitialize()
        {
            Core::DebugPrintF("Scene Manager DeInitialized (not implemented)\n");
        }

        void SceneManager::Update()
        {
            SceneManager& _instance = SceneManager::instance();
            _instance.currentScene->Update();
        }

        void SceneManager::Render()
        {
            SceneManager& _instance = SceneManager::instance();
            _instance.currentScene->Render();
        }
        
        void SceneManager::LoadScene(std::string sceneName)
        {
            SceneManager& _manager = SceneManager::instance();

            UnloadScene();

            SceneManager& _instance = SceneManager::instance();

            for (auto const scene : _manager.scenes)
            {
                if (_instance.currentScene->Name() == sceneName)
                {
                    _instance.currentScene = (Scene*) &scene;
                    break;
                }
            }

            //_instance.currentScene->Load();
        }

        void SceneManager::LoadSceneAsync(std::string sceneName)
        {
            Core::DebugPrintF("Scene Manager LoadSceneAsync (not implemented)\n");
        }
        
        void SceneManager::UnloadScene()
        {
            Core::DebugPrintF("Scene Manager UnloadScene (not implemented)\n");
        }

        json SceneManager::LoadJSON(std::string filepath)
        {
            Core::File file;
            try {
                file.Open(filepath, FileMode::ReadText);
            }
            catch (FileException e) {
                Core::DebugPrintF("Scene file not found.");
                return true;
            }

            //get size of file
            size_t size = file.SizeBytes();
            if (size == -1)
            {
                Core::DebugPrintF("Scene file is corrupted.");
                return true;
            }
            BYTE* byteArray = (BYTE*)malloc(size + 1);
            memset(byteArray, '\0', size + 1);
            file.Read(byteArray, size);
            file.Close();

            json data = json::parse((char*)byteArray);

            free(byteArray);

            return data;
        }
    }
}
