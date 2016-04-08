
#include "ht_cfactory.h"

/*[[[cog
import cog
from os import listdir
from os.path import isfile, join

files = [f for f in listdir('../../../../HatchitGame/include/') if isfile(join('../../../../HatchitGame/include/', f))]

ComponentFiles = []

for filename in files:
    with open("../../../../HatchitGame/include/" + filename, 'r') as f:
        for line in f:
            if ": public Component" in line or ": Component" in line:
                words = line.strip().split(' ')
                ComponentFiles.append(filename)


for t in ComponentFiles:
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
                from os import listdir
                from os.path import isfile, join

                files = [f for f in listdir('../../../../HatchitGame/include/') if isfile(join('../../../../HatchitGame/include/', f))]
                
                ComponentTypes = []
                
                for filename in files:
                    with open("../../../../HatchitGame/include/" + filename, 'r') as f:
                        for line in f:
                            if ": public Component" in line or ": Component" in line:
                                words = line.strip().split(' ')
                                ComponentTypes.append(words[1])
                
                for t in ComponentTypes:
                    cog.outl("""if (type == "%s") return new %s();""" % (t, t));
            
            ]]]*/
            if (type == "MeshRenderer") return new MeshRenderer();
            if (type == "TestComponent") return new TestComponent();
            //[[[end]]]
            return nullptr;
        }
    }
}
