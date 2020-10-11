#include "visualizer.h"

#include "OgreEntity.h"

namespace visualizer {

//! [constructor]
VisualizerApp::VisualizerApp()
    : OgreBites::ApplicationContext("OgreTutorialApp") {}
//! [constructor]

//! [key_handler]
bool VisualizerApp::keyPressed(const OgreBites::KeyboardEvent& evt) {
  if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) {
    getRoot()->queueEndRendering();
  }
  return true;
}
//! [key_handler]

//! [setup]
void VisualizerApp::setup(void) {
  // do not forget to call the base first
  OgreBites::ApplicationContext::setup();

  // register for input events
  addInputListener(this);

  // get a pointer to the already created root
  Ogre::Root* root = getRoot();
  Ogre::SceneManager* scnMgr = root->createSceneManager();

  // register our scene with the RTSS
  Ogre::RTShader::ShaderGenerator* shadergen =
      Ogre::RTShader::ShaderGenerator::getSingletonPtr();
  shadergen->addSceneManager(scnMgr);

  scnMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);

  scnMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

  // without light we would just get a black screen
  Ogre::Light* light = scnMgr->createLight("MainLight");
  Ogre::SceneNode* lightNode =
      scnMgr->getRootSceneNode()->createChildSceneNode();
  lightNode->setPosition(20, 80, 50);
  lightNode->attachObject(light);

  // also need to tell where we are
  Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  camNode->setPosition(50, 140, 50);
  camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);

  // create the camera
  Ogre::Camera* cam = scnMgr->createCamera("myCam");
  cam->setNearClipDistance(5);  // specific to this sample
  cam->setAutoAspectRatio(true);
  camNode->attachObject(cam);

  // and tell it to render into the main window
  getRenderWindow()->addViewport(cam);

  // finally something to render
  Ogre::Entity* ent = scnMgr->createEntity("cube.mesh");
  Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
  node->attachObject(dynamic_cast<Ogre::MovableObject*>(ent));

  Ogre::ManualObject* ground = scnMgr->createManualObject("ground");
  InitializeManualGround(ground);
  scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(
      dynamic_cast<Ogre::MovableObject*>(ground));
}
//! [setup]

void VisualizerApp::InitializeManualGround(Ogre::ManualObject* ground) {
  ground->begin("Examples/GrassFloor", Ogre::RenderOperation::OT_TRIANGLE_LIST);
  // Add vertices.
  ground->position(-70, 0, -70);
  ground->normal(0, 1, 0);
  ground->textureCoord(0, 0);
  // ground->colour(Ogre::ColourValue::White);

  ground->position(-70, 0, 70);
  ground->normal(0, 1, 0);
  ground->textureCoord(0, 1);
  // ground->colour(Ogre::ColourValue::White);

  ground->position(70, 0, 70);
  ground->normal(0, 1, 0);
  ground->textureCoord(1, 1);
  // ground->colour(Ogre::ColourValue::White);

  ground->position(70, 0, -70);
  ground->normal(0, 1, 0);
  ground->textureCoord(1, 0);
  // ground->colour(Ogre::ColourValue::White);

  ground->quad(0, 1, 2, 3);
  ground->end();
}

}  // namespace visualizer