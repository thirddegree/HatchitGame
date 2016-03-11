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

#if defined(DEBUG) || defined(_DEBUG)
    #include <ht_debug.h>
#endif

#include <set>

namespace Hatchit {

    namespace Game {

        using JSON = nlohmann::json;
        using JsonVerifyFunc = bool(JSON::*)() const;

        /** Shorthand for retrieving a string from a JSON object. */
        #define ExtractStringFromJSON(json, name, out) _ExtractFromJSON<std::string>(json, &JSON::is_string, name, out)

        /**
         * \brief Attempts to extract a value from a JSON object.
         *
         * \param json The JSON object.
         * \param verify The JSON type verification function.
         * \param name The name of the value to retrieve.
         * \param out The output variable.
         * \return True if the extraction was successful, false if not.
         */
        template<typename T>
        static inline bool _ExtractFromJSON(const JSON& json, JsonVerifyFunc verify, const std::string& name, T& out)
        {
            auto  search = json.find(name);
            auto& object = *search;

            if (search == json.end() || !(object.*verify)())
            {
                return false;
            }

            out = search->get<T>();
            return true;
        }

        /**
         * \brief Attempts to extract a Guid from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the Guid to retrieve.
         * \param out The output Guid.
         * \return True if the extraction was successful, false if not.
         */
        static __forceinline bool ExtractGuidFromJSON(const JSON& json, const std::string& name, Guid& out)
        {
            std::string guidText;
            return ExtractStringFromJSON(json, name, guidText) && Guid::Parse(guidText, out);
        }

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
         * \brief Creates a new, empty scene.
         */
        Scene::Scene()
        {
        }

        /**
         * \brief Destroys this scene.
         */
        Scene::~Scene()
        {

        }

        /**
         * \brief Creates a game object inside of this scene.
         */
        GameObject* Scene::CreateGameObject()
        {
            Guid guid;
            return CreateGameObject(guid);
        }

        /**
         * \brief Creates a new game object with the given GUID.
         *
         * \param guid The game object's globally-unique identifier.
         * \return The new game object.
         */
        GameObject* Scene::CreateGameObject(const Guid& guid)
        {
            m_gameObjects.emplace_back(guid);
            return &m_gameObjects.back();
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
            if (!ExtractStringFromJSON(m_description, "Name", m_name))
            {
#if defined(DEBUG) || defined(_DEBUG)
                Core::DebugPrintF("Failed to find property 'Name' in scene description!\n");
#endif
                return false;
            }

            // Get this scene's Guid
            if (!ExtractGuidFromJSON(m_description, "GUID", m_guid))
            {
#if defined(DEBUG) || defined(_DEBUG)
                Core::DebugPrintF("Failed to find property 'GUID' in scene description!\n");
#endif
                return false;
            }

            // Get the Guids for every GameObject in the scene.
            std::set<std::string> guids{};
            if (!ExtractContainerFromJSON<std::set<std::string>>(m_description, "GUIDs", guids))
            {
#if defined(DEBUG) || defined(_DEBUG)
                Core::DebugPrintF("Failed to find property 'GUIDs' in scene description!\n");
#endif
                return false;
            }

            // Get an array of all the GameObjects in the scene.
            std::vector<JSON> gameObjs{};
            if (!ExtractContainerFromJSON<std::vector<JSON>>(m_description, "GameObjects", gameObjs))
            {
#if defined(DEBUG) || defined(_DEBUG)
                Core::DebugPrintF("Failed to find property 'GameObjects' in scene description!\n");
#endif
                return false;
            }

            // Begin parsing the GameObjects in the scene.
            Guid id;
            for (JSON& obj : gameObjs)
            {
                if (!ExtractGuidFromJSON(obj, "GUID", id))
                {
#if defined(DEBUG) || defined(_DEBUG)
                    Core::DebugPrintF("Failed to find property 'GUID' on GameObject in scene description!\n");
#endif
                    return false;
                }

                /**< TODO: Validate GUID contained in guids. */

                if (!ParseGameObject(obj))
                {
#if defined(DEBUG) || defined(_DEBUG)
                    Core::DebugPrintF("Failed to parse GameObject with Guid %s in scene description!\n", id.ToString());
#endif
                    return false;
                }
            }

            return true;
        }

        bool Scene::ParseGameObject(JSON& obj)
        {
            /**< Add GameObject parsing code! */
            return true;
        }

        bool Scene::ParseComponent(JSON& obj)
        {
            /**< Add Component parsing code! */
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
#if defined(DEBUG) || defined(_DEBUG)
                Core::DebugPrintF("Failed to parse scene JSON!\n");
#endif
                data = JSON::object();
                loaded = false;
            }

            return loaded;
        }

        /**
         * \brief Gets this scene's name.
         */
        std::string Scene::Name() const
        {
            return m_name;
        }

        /**
         * \brief Renders this scene.
         */
        void Scene::Render()
        {
            for (GameObject& obj : m_gameObjects)
            {
                Transform *t = obj.GetTransform();
                t->UpdateWorldMatrix();
            }
        }
        
        /**
         * \brief Updates this scene.
         */
        void Scene::Update()
        {
            for (GameObject& obj : m_gameObjects)
            {
                obj.Update();
            }
        }
        
        /**
         * \brief Unloads this scene and its game objects.
         */
        void Scene::Unload()
        {
            Core::DebugPrintF("TODO - Scene::Unload()\n");
        }
    }
}
