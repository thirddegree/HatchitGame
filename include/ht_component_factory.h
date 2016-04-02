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

#include <ht_debug.h>
#include <ht_guid.h>
#include <ht_component.h>

#include <json.hpp>

#include <unordered_map>

namespace  Hatchit {
    namespace Game {
        using ComponentToJSON = nlohmann::json (*)(Component*);
        using JSONToComponent = Component* (*)(nlohmann::json&);

        class ComponentFactory
        {
        public:
            template <typename T>
            static bool RegisterComponentToJSON(ComponentToJSON callback);

            template <typename T>
            static bool RegisterJSONToComponent(JSONToComponent callback);

            ComponentFactory(void) = delete;
            ~ComponentFactory(void) = delete;
            ComponentFactory(const ComponentFactory& rhs) = delete;
            ComponentFactory(ComponentFactory&& rhs) = delete;
            ComponentFactory& operator=(const ComponentFactory& rhs) = delete;
            ComponentFactory& operator=(ComponentFactory&& rhs) = delete;

        private:
            std::unordered_map<Core::Guid, ComponentToJSON> m_componentToJson;
            std::unordered_map<Core::Guid, JSONToComponent> m_jsonToComponent;
        };

        template <typename T>
        static bool ComponentFactory::RegisterComponentToJSON(ComponentToJSON callback)
        {
            HT_DEBUG_PRINTF("ComponentFactory::RegisterComponentToJSON unimplemented!\n");
            return false;
        }

        template <typename T>
        static bool ComponentFactory::RegisterJSONToComponent(JSONToComponent callback)
        {
            HT_DEBUG_PRINTF("ComponentFactory::RegisterJSONToComponent unimplemented!\n");
            return false;
        }
    }
}

