#include "OgreApplicationContext.h"
#include "OgreApplicationContextBase.h"
#include "OgreRenderWindow.h"
#include "OgreRoot.h"

namespace visualizer {

class VisualizerApp : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    VisualizerApp();
    void setup();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:
    void InitializeManualGround(Ogre::ManualObject* ground);
};

}  // namespace visualizer