#include "camera.hpp"

// Constructeur
Camera::Camera(ISceneManager& smgr, ITriangleSelector& selector)
{
	this->initVariables();
	this->initKeysCamera();
	this->initCamera(smgr);
    this->render(smgr,selector);
}

// Destructeur
Camera::~Camera()
{
	delete this->nodeCamera;
}


// Fonctions initialisation
void Camera::initVariables()
{
	this->nodeCamera = nullptr;
}


void Camera::initKeysCamera()
{
    this->keyMap[0].Action = EKA_MOVE_FORWARD;
    this->keyMap[0].KeyCode = KEY_UP;
    this->keyMap[1].Action = EKA_MOVE_FORWARD;
    this->keyMap[1].KeyCode = KEY_KEY_Z;

    this->keyMap[2].Action = EKA_MOVE_BACKWARD;
    this->keyMap[2].KeyCode = KEY_DOWN;
    this->keyMap[3].Action = EKA_MOVE_BACKWARD;
    this->keyMap[3].KeyCode = KEY_KEY_S;

    this->keyMap[4].Action = EKA_STRAFE_LEFT;
    this->keyMap[4].KeyCode = KEY_LEFT;
    this->keyMap[5].Action = EKA_STRAFE_LEFT;
    this->keyMap[5].KeyCode = KEY_KEY_Q;

    this->keyMap[6].Action = EKA_STRAFE_RIGHT;
    this->keyMap[6].KeyCode = KEY_RIGHT;
    this->keyMap[7].Action = EKA_STRAFE_RIGHT;
    this->keyMap[7].KeyCode = KEY_KEY_D;

    this->keyMap[8].Action = EKA_JUMP_UP;
    this->keyMap[8].KeyCode = KEY_SPACE;
}

void Camera::initCamera(ISceneManager& smgr)
{
	
	nodeCamera = smgr.addCameraSceneNodeFPS(0, 100.0f, .3f, 0, this->keyMap, 9, true, 10.f);

    nodeCamera->setDebugDataVisible(irr::scene::EDS_BBOX);
    nodeCamera->setPosition(core::vector3df(50,300,-60));
    nodeCamera->setTarget(core::vector3df(-70,30,-60));
}

// Colision du mesh avec l'environnement (collision du joueur (joueur rattaché au camera
void Camera::render(ISceneManager& smgr, ITriangleSelector& selector) 
{
    this->animCamera = smgr.createCollisionResponseAnimator(
                &selector, this->nodeCamera,core::vector3df(30,40,30) ,
                core::vector3df(0,-10,0), core::vector3df(0,60,0));
    this->nodeCamera->addAnimator(animCamera);
    this->animCamera->drop();  // And likewise, drop the animator when we're done referring to it.
}

void Camera::update()
{
	//system("clear");

}
// Accesseurs
ICameraSceneNode* Camera::getNode() const
{
	return this->nodeCamera;
}