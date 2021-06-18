#include "librairies.hpp"
#include "player.hpp"
#include "camera.hpp"




#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

class Game
{
	E_DRIVER_TYPE driverType;
	IrrlichtDevice* device;
	ISceneManager* smgr;
	IVideoDriver* driver;
	ITriangleSelector* selector;
	IAnimatedMesh* meshScene;
	IMeshSceneNode* nodeScene;
	SMaterial material;
	MyEventReceiver* receiver;

	int lastFPS;
	int fps;
	Player* player;
	Camera* camera;

	// Fonctions privées
	void initVariables();
	void initWindow();
	void initScene();
	void initPlayer();
	void initCamera();
	void initEnemy();
public:
	// constructeur 
	Game();

	// Destructeur
	~Game();


	// Fonctions
	void run();
	void update();
	void render();
	void drop();
	void yield();
	void updateFps();


	// Accesseurs
	bool running() const;
	bool isWindowActive() const;

};