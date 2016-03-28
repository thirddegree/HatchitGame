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

#include <ht_scene.h>
#include <ht_jsonhelper.h>
#if defined(DEBUG) || defined(_DEBUG)
    #include <ht_debug.h>
#endif

namespace Hatchit {

    namespace Game {

        using JSON = nlohmann::json;
        using Core::Guid;
        using Core::_JsonExtractValue;

        /**
        * \brief Attempts to extract a std::vector from a JSON object.
        * \tparam T A JSON value type.
        * \param json   The JSON object to examine.
        * \param key    The key to locate in the JSON object.
        * \param value  The std::vector to insert into.
        * \return true if the std::vector could be successfully extracted.
        */
        template <typename Container>
        static inline bool ExtractContainerFromJSON(const JSON& json, const std::string& key, Container& value)
        {
            JSON::const_iterator iter = json.find(key);
            if (iter == json.cend() || !iter->is_array())
            {
                return false;
            }

            value = iter->get<Container>();

            return true;
        }

        /**
        * \brief Gets this scene's name.
        */
        std::string Scene::Name() const
        {
            return m_name;
        }

        /**
         * \brief Gets this scene's Guid.
         *
         * \return This scene's Guid.
         */
        const Guid& Scene::GUID() const
        {
            return m_guid;
        }

        /**
         * \brief Checks to see if this scene is cached.
         */
        bool Scene::IsCached() const
        {
            static const JSON s_DefaultObject = JSON::object();

            return m_description != s_DefaultObject;
        }

        /**
         * \brief Attempts to load this scene from the cache.
         */
        bool Scene::LoadFromCache()
        {
            // If we're not cached, then we can't load from the cache
            if (!IsCached())
            {
                return false;
            }

            // Get this scene's name
            if (!JsonExtractString(m_description, "Name", m_name))
            {
                HT_DEBUG_PRINTF("Failed to find property 'Name' in scene description!\n");
                return false;
            }

            // Get this scene's Guid
            if (!JsonExtractGuid(m_description, "GUID", m_guid))
            {
                HT_DEBUG_PRINTF("Failed to find property 'GUID' in scene description!\n");
                return false;
            }

            // Get the Guids for every GameObject in the scene.
            std::vector<std::string> string_guids{};
            if (!ExtractContainerFromJSON(m_description, "GUIDs", string_guids))
            {
                HT_DEBUG_PRINTF("Failed to find property 'GUIDs' in scene description!\n");
                return false;
            }

            // Parse the Guid strings into Guids.
            std::unordered_set<Guid> guids{};
            for (const std::string& string_guid : string_guids)
            {
                Guid id;
                if (!Guid::Parse(string_guid, id))
                {
                    HT_DEBUG_PRINTF("Failed to parse Guid %s in scene description!\n", string_guid);
                    return false;
                }

                guids.insert(id);
            }

            // Get an array of all the JSON GameObjects in the scene.
            std::vector<JSON> json_gameobjs{};
            if (!ExtractContainerFromJSON(m_description, "GameObjects", json_gameobjs))
            {
                HT_DEBUG_PRINTF("Failed to find property 'GameObjects' in scene description!\n");
                return false;
            }

            // Attempt to parse the JSON GameObjects.
            std::unordered_map<Guid, GameObject*> guid_to_obj{};
            std::unordered_map<Guid, JSON> guid_to_json{};
            for (const JSON& json_obj : json_gameobjs)
            {
                // Attempt to parse a GameObject from the provided JSON.
                GameObject obj;
                if (!ParseGameObject(json_obj, obj))
                {
                    HT_DEBUG_PRINTF("Failed to parse GameObject in scene description!\n");
                    return false;
                }

                // Validate that the Guid for the parsed GameObject is present in the master list.
                const Guid& id = obj.GetGuid();
                std::unordered_set<Guid>::const_iterator iter = guids.find(id);
                if (iter == guids.cend())
                {
                    HT_DEBUG_PRINTF("Failed to locate %s within 'GUIDs' array in scene description!\n", id.ToString());
                    return false;
                }

                GameObject* allocated_obj = new GameObject(std::move(obj));
                guid_to_obj.insert(std::make_pair(id, allocated_obj));
                guid_to_json.insert(std::make_pair(id, json_obj));
            }

            // Handles all GameObject parent/child arrangements.
            for (const Guid& id : guids)
            {
                ParseChildGameObjects(id, guid_to_obj, guid_to_json);
            }

            // Copy the remaining top-level GameObjects into std::vector.
            for (const std::pair<Guid, GameObject*>& guid_obj_pair : guid_to_obj)
            {
                m_gameObjects.push_back(guid_obj_pair.second);
            }

            return true;
        }

        void Scene::ParseChildGameObjects(const Guid& id, std::unordered_map<Guid, GameObject*>& guid_to_obj, std::unordered_map<Guid, JSON>& guid_to_json)
        {
            std::unordered_map<Guid, GameObject*>::const_iterator obj_iter = guid_to_obj.find(id);
            std::unordered_map<Guid, JSON>::const_iterator json_iter = guid_to_json.find(id);
            if ((obj_iter == guid_to_obj.cend()) || (json_iter == guid_to_json.cend()))
                return;

            const JSON& json_obj = json_iter->second;
            GameObject* obj = obj_iter->second;

            std::vector<std::string> string_guids{};
            if (!ExtractContainerFromJSON(json_obj, "Children", string_guids))
                return;

            std::unordered_set<Guid> child_guids{};
            for (const std::string& string_guid : string_guids)
            {
                Guid id;
                if (!Guid::Parse(string_guid, id))
                    continue;

                child_guids.insert(id);
            }

            for (const Guid& child_guid : child_guids)
            {
                std::unordered_map<Guid, GameObject*>::const_iterator child_obj_iter = guid_to_obj.find(child_guid);
                std::unordered_map<Guid, JSON>::const_iterator child_json_iter = guid_to_json.find(child_guid);
                if ((child_obj_iter == guid_to_obj.cend()) || (child_json_iter == guid_to_json.cend()))
                    continue;

                ParseChildGameObjects(child_guid, guid_to_obj, guid_to_json);

                GameObject* child_obj = child_obj_iter->second;
                obj->AddChild(child_obj);

                guid_to_obj.erase(child_guid);
                guid_to_json.erase(child_guid);
            }
        }

        bool Scene::ParseGameObject(const JSON& obj, GameObject& out)
        {
            // Extract the GameObject's GUID.
            Guid id;
            if (!JsonExtractGuid(obj, "GUID", id))
            {
                HT_DEBUG_PRINTF("Failed to find property 'GUID' on GameObject in scene description!\n");
                return false;
            }

            // Extract the GameObject's Name.
            std::string name;
            if (!JsonExtractString(obj, "Name", name))
            {
                HT_DEBUG_PRINTF("Failed to find property 'Name' on GameObject %s in scene description!\n", id.ToString());
                return false;
            }

            // Extract the GameObject's enabled state.
            bool enabled = false;
            //ExtractBoolFromJSON(obj, "Enabled", enabled)

            // Attempt to extract the GameObject's Transform.
            Transform t = ParseTransform(obj);

            // Construct the GameObject using the GUID, Name, and Transform extracted from JSON.
            out = GameObject{id, name, t, enabled};

            // Attempt to extract a std::vector of Component JSON objects.
            std::vector<JSON> components;
            if (ExtractContainerFromJSON(obj, "Components", components))
            {
                for (const JSON& json_component : components)
                {
                    if (!ParseComponent(json_component, out))
                    {
                        HT_DEBUG_PRINTF("Failed to parse Component %s on GameObject %s in the scene description!\n", json_component.dump(), id.ToString());
                    }
                }
            }

            return true;
        }

        Transform Scene::ParseTransform(const JSON& obj)
        {
            JSON::const_iterator iter = obj.find("Transform");
            if (iter == obj.cend())
            {
                HT_DEBUG_PRINTF("Failed to locate property 'Transform,' using default values!\n");
                return Transform{};
            }

            JSON json_transform = *iter;

            std::vector<float> position;
            if (!ExtractContainerFromJSON(json_transform, "Position", position) || (position.size() != 3))
            {
                HT_DEBUG_PRINTF("Failed to parse property 'Position' on Transform, defaulting to {0.0f, 0.0f, 0.0f}\n");
                position = {0.0f, 0.0f, 0.0f};
            }

            std::vector<float> rotation;
            if (!ExtractContainerFromJSON(json_transform, "Rotation", rotation) || (rotation.size() != 3))
            {
                HT_DEBUG_PRINTF("Failed to parse property 'Rotation' on Transform, defaulting to {0.0f, 0.0f, 0.0f}\n");
                rotation = {0.0f, 0.0f, 0.0f};
            }

            std::vector<float> scale;
            if (!ExtractContainerFromJSON(json_transform, "Scale", scale) || (scale.size() != 3))
            {
                HT_DEBUG_PRINTF("Failed to parse property 'Scale' on Transform, defaulting to {1.0f, 1.0f, 1.0f}\n");
                scale = {1.0f, 1.0f, 1.0f};
            }

            return Transform{position[0], position[1], position[2], rotation[0], rotation[1], rotation[2], scale[0], scale[1], scale[2]};
        }

        bool Scene::ParseComponent(const JSON& obj, GameObject& out)
        {
            std::string component_type;
            if (!JsonExtractString(obj, "Name", component_type))
            {
                HT_DEBUG_PRINTF("Failed to locate property 'Name' on Component in scene description!\n");
                return false;
            }

            if (component_type == "TestComponent")
            {
                out.AddComponent<TestComponent>();
            }

            // TODO: Add cases for each Component type here.

            else
            {
                HT_DEBUG_PRINTF("Unknown Component type %s in scene description!\n", component_type);
                return false;
            }

            return true;
        }

        /**
         * \brief Attempts to load scene data from a file.
         *
         * \param file The file to load from.
         * \return True if loading was successful, false if not.
         */
        bool Scene::LoadFromFile(Core::File& file)
        {
            // Reserve enough memory to read the file
            std::string contents;
            contents.resize(file.SizeBytes());
            
            // Read the file
            file.Read(reinterpret_cast<BYTE*>(&contents[0]), contents.length());

            // Now parse the contents from memory
            return LoadFromMemory(contents);
        }

        /**
         * \brief Attempts to load scene data from memory.
         *
         * \param jsonText The JSON-encoded scene data.
         * \return True if loading was successful, false if not.
         */
        bool Scene::LoadFromMemory(const std::string& jsonText)
        {
            JSON data;
            bool loaded = false;

            try
            {
                // Attempt to parse the JSON
                data = JSON::parse(jsonText);

                // If we get here, then the JSON parsed successfully
                m_description = data;
                loaded = LoadFromCache(); // Loads from m_description
            }
            catch (...)
            {
                HT_DEBUG_PRINTF("Failed to parse scene JSON!\n");
                data = JSON::object();
                loaded = false;
            }

            return loaded;
        }

        void Scene::Init()
        {
            for (GameObject* gameObject : m_gameObjects)
            {
                //gameObject->OnInit();
            }
            for (GameObject* gameObject : m_gameObjects)
            {
                if (gameObject->GetEnabled())
                    gameObject->OnEnabled();
            }
        }

        /**
         * \brief Renders this scene.
         */
        void Scene::Render()
        {
            for (GameObject* obj : m_gameObjects)
            {
                Transform& t = obj->GetTransform();
                t.UpdateWorldMatrix();
            }
        }
        
        /**
         * \brief Updates this scene.
         */
        void Scene::Update()
        {
            for (GameObject* obj : m_gameObjects)
            {
                obj->Update();
            }
        }
        
        /**
         * \brief Unloads this scene and its game objects.
         */
        void Scene::Unload()
        {
            for (GameObject* gameObject : m_gameObjects)
            {
                gameObject->Destroy();
            }
            for (GameObject* gameObject : m_gameObjects)
            {
                delete gameObject;
            }
            m_gameObjects.clear();
        }
    }
}
