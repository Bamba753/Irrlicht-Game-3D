#ifndef __CAMERA__
#define __CAMERA__

#include "librairies.hpp"

class Camera
{

	// Variables
	SKeyMap keyMap[9];
	ICameraSceneNode* nodeCamera;
	ISceneNodeAnimator* animCamera;

	// Fonctions privees 
	void initVariables();
	void initKeysCamera();
	void initCamera(ISceneManager& smgr);

	public :

	// Constructeur
	Camera(ISceneManager& smgr, ITriangleSelector& selector);

	// Destructeur
	~Camera();

	// Fonctions
	void render(ISceneManager& smgr, ITriangleSelector& selector);
	void update();
	// Acesseurs
	ICameraSceneNode* getNode() const;
};


#endif