
#include "ht_component_factory.h"

/*[[[cog
import cog
from os import listdir
from os.path import isfile, join

class Node():
    def __init__(self, filename, className, superName):
        self.filename = filename
        self.className = className
        self.superName = superName
        self.children = []

def findChildren(classes, componentList, components, superName):
    for cl in classes:
        if cl.superName == superName:
            components.append(Node(cl.filename, cl.className, cl.superName))
            componentList.append(cl)

classes = []
componentList = []
components = []

files = [f for f in listdir('../../../HatchitGame/include/') if isfile(join('../../../HatchitGame/include/', f))]

for filename in files:
    with open("../../../HatchitGame/include/" + filename, 'r') as f:
        for line in f:
            if "class" in line and " : " in line and not ("enum" in line):
                words = line.strip().split(" : ")
                className = words[0].strip().split(' ')[-1]
                supers = words[1].strip().split(' ')
                for superName in supers:
                    if not (superName == "public") and not (superName == ","):
                        classes.append(Node(filename, className, superName))

findChildren(classes, componentList, components, "Component")
while len(componentList) > 0:
    n = componentList.pop()
    findChildren(classes, componentList, components, n.className)

for t in components:
    cog.outl("#include <%s>" % t.filename);

]]]*/
#include <ht_camera_component.h>
#include <ht_meshrenderer_component.h>
#include <ht_test_component.h>
#include <ht_tween_component.h>
#include <ht_tween_position.h>
#include <ht_tween_rotation.h>
#include <ht_tween_scale.h>
//[[[end]]]

namespace Hatchit {

    namespace Game {

        Component* ComponentFactory::MakeComponent(std::string type)
        {
            /*[[[cog
                
                import cog
                from os import listdir
                from os.path import isfile, join

                files = [f for f in listdir('../../../HatchitGame/include/') if isfile(join('../../../HatchitGame/include/', f))]
                
                class Node():
                    def __init__(self, filename, className, superName):
                        self.filename = filename
                        self.className = className
                        self.superName = superName
                        self.children = []
                    def addChild(self, child):
                        self.children.append(child)

                def findChildren(classes, componentList, components, superName):
                    for cl in classes:
                        if cl.superName == superName:
                            componentList.append(cl)
                            components.append(Node(cl.filename, cl.className, cl.superName))

                classes = []
                componentList = []
                components = []

                for filename in files:
                    with open("../../../HatchitGame/include/" + filename, 'r') as f:
                        for line in f:
                            if "class" in line and " : " in line and not ("enum" in line):
                                words = line.strip().split(" : ")
                                className = words[0].strip().split(' ')[-1]
                                supers = words[1].strip().split(' ')
                                for superName in supers:
                                    if not (superName == "public") and not (superName == ","):
                                        classes.append(Node(filename, className, superName))

                findChildren(classes, componentList, components, "Component")
                while len(componentList) > 0:
                    n = componentList.pop()
                    findChildren(classes, componentList, components, n.className)
                
                for t in components:
                    cog.outl("""if (type == "%s") return new %s();""" % (t.className, t.className));
                
            ]]]*/
            if (type == "Camera") return new Camera();
            if (type == "MeshRenderer") return new MeshRenderer();
            if (type == "TestComponent") return new TestComponent();
            if (type == "TweenComponent") return new TweenComponent();
            if (type == "TweenPosition") return new TweenPosition();
            if (type == "TweenRotation") return new TweenRotation();
            if (type == "TweenScale") return new TweenScale();
            //[[[end]]]
            return nullptr;
        }
    }
}
