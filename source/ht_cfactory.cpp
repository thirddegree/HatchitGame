
#include "ht_cfactory.h"

/*[[[cog
import cog
ComponentTypes = ['ht_meshrenderer_component.h', 'ht_test_component.h']
for t in ComponentTypes:
    cog.outl("#include <%s>" % t);

]]]*/
#include <ht_meshrenderer_component.h>
#include <ht_test_component.h>
//[[[end]]]

namespace Hatchit {
    namespace Game {
        Component* CFactory::MakeComponent(std::string type)
        {
            /*[[[cog
                import cog
                ComponentTypes = ['MeshRenderer', 'TestComponent']
                for t in ComponentTypes:
                    cog.outl("""if (type == "%s") return new %s();""" % (t, t));
            
            ]]]*/
            if (type == "MeshRenderer") return new MeshRenderer();
            if (type == "TestComponent") return new TestComponent();
            //[[[end]]]
        }
    }
}
