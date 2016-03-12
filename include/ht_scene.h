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

#include <json.hpp>

#include <vector>
#include <unordered_set>

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
            Scene(void) = default;
            ~Scene(void) = default;
            Scene(const Scene& rhs) = default;
            Scene(Scene&& rhs) = default;
            Scene& operator=(const Scene& rhs) = default;
            Scene& operator=(Scene&& rhs) = default;

            /**
             * \brief Creates a game object inside of this scene.
             */
            GameObject* CreateGameObject();

            /**
            * \brief Gets this scene's name.
            */
            std::string Name() const;

            /**
             * \brief Gets this scene's Guid.
             *
             * \return This scene's Guid.
             */
            const Guid& GUID() const;

            /**
             * \brief Checks to see if this scene is cached.
             */
            bool IsCached() const;
            
            /**
             * \brief Attempts to load this scene from the cache.
             */
            bool LoadFromCache();

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
             * \brief Renders this scene.
             */
            void Render(void);
            
            /**
             * \brief Updates this scene.
             */
            void Update(void);

            /**
             * \brief Unloads this scene and its game objects.
             */
            void Unload(void);

        private:
            /**
             * \brief Creates a new game object with the given GUID.
             * \param guid The game object's globally-unique identifier.
             * \return The new game object.
             */
            GameObject* CreateGameObject(const Guid& guid);

            /**
            * \brief Attempts to parse a GameObject from the provided JSON.
            * \param obj    The JSON object to parse.
            * \return true if the GameObject was parsed successfully.
            */
            bool ParseGameObject(const nlohmann::json& obj, const std::unordered_set<Guid>& guids);

            /**
            * \brief Attempts to parse a Transform from the provided JSON.
            * \param obj    The JSON object to parse.
            * \param out    The Transform that will hold the result.
            * \return true if the Transform was parsed successfully.
            */
            bool ParseTransform(const nlohmann::json& obj, Transform& out);

            /**
            * \brief Attempts to parse a Component from the provided JSON.
            * \param obj    The JSON object to parse.
            * \return true if the Component was parsed successfully.
            */
            bool ParseComponent(const nlohmann::json& obj);

            std::string m_name; /**< The name associated with this scene. */
            Guid m_guid; /**< The Guid associated with this scene. */
            nlohmann::json m_description; /**< The JSON description of the scene. */
            std::vector<GameObject> m_gameObjects; /**< std::vector of GameObjects present in the scene. */
        };
    }
}
