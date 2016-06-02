/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 Third-Degree
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
#include <ht_scene_resource.h>

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
             * \brief De-initializes the scene manager.
             */
            static void Deinitialize();

            /**
             * \brief Initializes the scene manager.
             * \return true if the SceneManager could be initialized, false otherwise.
             */
            static bool Initialize();

            /**
             * \brief Loads the given scene.
             * \param sceneName         The name of the next Scene to load.
             * \return true if the Scene was successfully loaded, false otherwise.
             * \sa Scene(), Scene::LoadFromHandle()
             *
             * Unloads the current scene and loads in the specified scene.
             * If the scene does not exist in the list of scenes, an error is thrown.
             */
            static bool LoadScene(const std::string& sceneName);

            /**
             * \brief Updates the scene manager.
             */
            static void Update();

            SceneManager(void) = default;
            virtual ~SceneManager(void) = default;

        private:
            static std::string SCENE_LIST; /**< Name of the file containing the master scene list. */

            std::unordered_map<std::string, Resource::SceneHandle> m_sceneHandles; /**< Map of filenames to Scene JSON handles. */
            Scene* m_currentScene; /**< The currently loaded scene. */
        };
    }
}
