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
#include <ht_file.h>
#include <vector>
#include <unordered_map>

namespace Hatchit {

    namespace Game {

        /**
         * \brief Defines the singleton scene manager.
         */
        class HT_API SceneManager : public Core::Singleton<SceneManager>
        {
        public:
            /**
             * \brief Creates the scene manager.
             */
            SceneManager();

            /**
             * \brief Destroys the scene manager.
             */
            virtual ~SceneManager();

            /**
             * \brief De-initializes the scene manager.
             */
            static void Deinitialize();

            /**
             * \brief Initializes the scene manager.
             */
            static bool Initialize();

            /**
             * \brief Loads the given scene.
             *
             * Unloads the current scene and loads in the specified scene.
             * If the scene does not exist in the list of scenes, an error is thrown.
             */
            static bool LoadScene(const std::string& sceneName);

            /**
             * \brief Updates the scene manager.
             */
            static void Update();

        private:
            // TODO - Use something better than a vector
            std::vector<Scene> m_scenes;
            Scene* m_currentScene;
        };
    }
}
