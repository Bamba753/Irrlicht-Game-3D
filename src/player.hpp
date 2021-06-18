#ifndef __PLAYER__
#define __PLAYER__

#include "librairies.hpp"
#include "camera.hpp"
#include "gameEvent.hpp"
#include <math.h>  

#define PI 3.14159265


enum class playerState {MOVING, JUMPING, NOT_MOVING, TARGET};
class Player
{
	// Variables 
	int health;
	SMaterial materialPlayer;
    IAnimatedMesh* meshPlayer;
    IAnimatedMeshSceneNode* nodePlayer;
    IBillboardSceneNode * bill;
    ILightSceneNode * light;
    ISceneNode* highlightedSceneNode;
    ISceneCollisionManager* collMan;
    playerState currentState;
    int param;
    int t;
    vector3df posIni;


	// FOnctions privees
	void initVariables();
	void initPlayer(ISceneManager& smgr, IVideoDriver& driver, ITriangleSelector& selector, SMaterial& material);
	void initViseur(ISceneManager& smgr, IVideoDriver& driver);
	public :
	// Constructeur
	Player(ISceneManager& smgr, IVideoDriver& driver, ITriangleSelector& selector, SMaterial& material);

	// Destructeur
	~Player();

	// Fonctions
	void update(IVideoDriver& driver,Camera& camera, SMaterial& material, MyEventReceiver& receiver);
	void targetGun(IVideoDriver& driver,Camera& camera, SMaterial& material);
	void notMovingMovement();
	void targetMovement();
	void updateState(MyEventReceiver& receiver);
	void updatePlayerMovement();


	// Acesseurs

	
};


#endif 