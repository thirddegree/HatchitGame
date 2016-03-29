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
#include <ht_test_component.h>
#include <ht_meshrenderer_component.h>

#include <json.hpp>

#include <vector>
#include <unordered_set>
#include <unordered_map>

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
        friend class SceneManager;
        public:
            Scene(void) = default;
            ~Scene(void) = default;
            Scene(const Scene& rhs) = default;
            Scene(Scene&& rhs) = default;
            Scene& operator=(const Scene& rhs) = default;
            Scene& operator=(Scene&& rhs) = default;

            /**
            * \brief Gets this scene's name.
            */
            std::string Name() const;

            /**
             * \brief Gets this scene's Guid.
             *
             * \return This scene's Guid.
             */
            const Core::Guid& GUID() const;

            /**
             * \brief Checks to see if this scene is cached.
             */
            bool IsCached() const;
            
            /**
             * \brief Attempts to load this scene from the cache.
             * This method steps through the JSON file creating all the GameObjects in the scene.
             * \sa ParseChildGameObjects(), ParseGameObject(), ParseTransform(), ParseComponent()
             */
            bool LoadFromCache(void);

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

            /**
             * \brief Creates GameObject and adds it to the scene.
             */
            GameObject* CreateGameObject();

        private:

            /**
            * \brief Initializes GameObjects in scene
            */
            void Init();

            /**
            * \brief Recursively establishes the parent/child relationship of the GameObject linked to the provided Guid.
            * \param id                 The Guid of the GameObject to setup.
            * \param guid_to_obj        Mapping of Guids to GameObject pointers.
            * \param guid_to_json       Mapping of Guids to JSON objects.
            *
            * This method is recursively invoked on all the children of the GameObject listed in the JSON file.
            *
            * \sa ParseGameObject(), ParseTransform(), ParseComponent, LoadFromCache(), GameObject()
            */
            void ParseChildGameObjects(const Core::Guid& id, std::unordered_map<Core::Guid, GameObject*>& guid_to_obj, std::unordered_map<Core::Guid, nlohmann::json>& guid_to_json);

            /**
            * \brief Attempts to parse a GameObject from the provided JSON.
            * \param obj    The JSON object to parse.
            * \return true if the GameObject was parsed successfully.
            *
            * \sa ParseChildGameObjects(), ParseTransform(), ParseComponent(), LoadFromCache(), GameObject()
            */
            bool ParseGameObject(const nlohmann::json& obj, GameObject& out);

            /**
            * \brief Attempts to parse a Transform from the provided JSON.
            * \param obj    The JSON object to parse.
            * \return The resulting Transform.
            *
            * If there are any missing properties in the JSON, default values are substituted.
            *
            * \sa ParseChildGameObjects(), ParseGameObject(), ParseComponent(), LoadFromCache(), Transform()
            */
            Transform ParseTransform(const nlohmann::json& obj);

            /**
            * \brief Attempts to parse a Component from the provided JSON.
            * \param obj    The JSON object to parse.
            * \return true if the Component was parsed successfully.
            *
            * Code to parse new Component types should be added to this method.
            *
            * \sa ParseChildGameObjects(), ParseGameObject(), ParseTransform(), LoadFromCache(), Component()
            */
            bool ParseComponent(const nlohmann::json& obj, GameObject& out);

            std::string m_name; /**< The name associated with this scene. */
            Core::Guid m_guid; /**< The Guid associated with this scene. */
            nlohmann::json m_description; /**< The JSON description of the scene. */
            std::vector<GameObject*> m_gameObjects; /**< std::vector of GameObjects present in the scene. */
        };
    }
}
