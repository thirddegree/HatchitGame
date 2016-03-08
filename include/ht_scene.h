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
#include <ht_gameobject.h>
#include <ht_guid.h>
#include <ht_file.h>
#include <vector>
#include <ht_debug.h>

#ifdef HT_SYS_LINUX
    #include <cstdlib>
#endif

namespace Hatchit {

    namespace Game {

        /**
        * \brief Defines a scene.
        */
        class HT_API Scene
        {
        public:
            /**
             * \brief Creates a new, empty scene.
             */
            Scene();

            /**
             * \brief Destroys this scene.
             */
            ~Scene();

            /**
             * \brief Creates a game object inside of this scene.
             */
            GameObject* CreateGameObject();

            /**
             * \brief Gets this scene's Guid.
             *
             * \return This scene's Guid.
             */
            const Guid& GUID() const;

            /**
             * \brief Attempts to load scene data from a file.
             *
             * \param file The file to load from.
             * \return True if loading was successful, false if not.
             */
            bool LoadFromFile(Core::File& file);

            /**
             * \brief Attempts to load scene data from memory.
             *
             * \param json The JSON-encoded scene data.
             * \return True if loading was successful, false if not.
             */
            bool LoadFromMemory(const std::string& json);

            /**
             * \brief Gets this scene's name.
             */
            std::string Name() const;

            /**
             * \brief Updates this scene.
             */
            void Update();

            /**
             * \brief Renders this scene.
             */
            void Render();

        private:
            /**
             * \brief Creates a new game object with the given GUID.
             *
             * \param guid The game object's globally-unique identifier.
             * \return The new game object.
             */
            GameObject* CreateGameObject(const Guid& guid);

        private:
            Guid m_guid;
            std::vector<GameObject> m_gameObjects;
            std::string m_name;
        };
    }
}
