#pragma once

#include <string>
#include <ht_component.h>

namespace Hatchit {
    namespace Game {
        class ComponentFactory
        {
        public:
            static Component* MakeComponent(std::string type);
        };
    }
}
