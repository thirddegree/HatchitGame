#pragma once

#include <string>
#include <ht_component.h>

namespace Hatchit {
    namespace Game {
        class CFactory
        {
        public:
            Component* MakeComponent(std::string type);
        };
    }
}
