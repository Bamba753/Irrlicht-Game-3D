#include "game.hpp"


// Constructeurs
Game::Game()
{
	this->initVariables(); 
	this->initWindow();
	this->initScene();
	this->initCamera();
	this->initPlayer();
	
}

// Destructeurs
Game::~Game()
{
	delete this->device;
	delete this->smgr;
	delete this->driver;
	delete this->player;
	delete this->camera;
	delete this->receiver;
}


// Initialisation des paramètres de la fenetre
void Game::initWindow()
{
	this->driverType = video::EDT_OPENGL;
	this->receiver   = new MyEventReceiver();
	this->device     = createDevice(this->driverType, core::dimension2d<u32>(640, 480), 16, false, false, false, this->receiver);;
	this->driver     = device->getVideoDriver();
    this->smgr       = device->getSceneManager();
    this->device->getFileSystem()->addFileArchive("data/map-13tokay/map-13tokay.pk3");
    this->smgr->addCameraSceneNodeFPS();
    this->lastFPS    = -1;
}


// Initialisation des variables
void Game::initVariables()
{
	this->driverType  =    video::EDT_NULL;
 	this->device      =    nullptr;
	this->smgr        =    nullptr;
	this->driver      =    nullptr;
	this->player      =    nullptr;
	this->camera      =    nullptr;
	this->selector    =    0;
	this->meshScene   =    0;
	this->nodeScene   =    0;
}

void Game::initScene()
{
	this->meshScene = smgr->getMesh("13tokay.bsp");

    if (this->meshScene)
        this->nodeScene = this->smgr->addOctreeSceneNode(this->meshScene->getMesh(0));

    if (this->nodeScene)
    {
            this->nodeScene->setPosition(core::vector3df(100,-15.0,250));
            this->selector = smgr->createOctreeTriangleSelector(this->nodeScene->getMesh(), this->nodeScene, 128);
            this->nodeScene->setTriangleSelector(this->selector);
    }
}


// Initialisation du player
void Game::initPlayer()
{
	
	this->player = new Player(*this->smgr,*this->driver, *this->selector, this->material);
	Player::t = 0;
	this->device->getCursorControl()->setVisible(false);        
	//this->material.setTexture(0, 0);
    //this->material.Lighting = false;
}

// Initialisation du camera
void Game::initCamera()
{
	this->camera = new Camera(*this->smgr,*this->selector);
}

// Fonctions
void Game::run()
{
    while (this->running())
    {

        if (this->isWindowActive())
        {
            // Update
            this->update();
            // Render
            this->render();

            this->updateFps();
        }
        else this->yield();
    }

    this->drop();
}

 
void Game::update()
{
	// this->pollevent(); 
	this->player->update(*this->driver, *this->camera, this->material, *this->receiver);
	this->camera->update();
}

void Game::render()
{
	this->driver->beginScene(true, true, 0);
    this->smgr->drawAll();
    this->driver->endScene();
}

void Game::drop()
{
	// engine->drop();
    this->device->drop();
}

void Game::yield()
{
	this->device->yield();
}


void Game::updateFps()
{

    fps = this->driver->getFPS();

    if (this->lastFPS != fps)
    {
        core::stringw str = L"Game [";
        str += this->driver->getName();
        str += "] FPS:";
        str += fps;

        this->device->setWindowCaption(str.c_str());
        this->lastFPS = fps;
    }
}

// Acesseurs
bool Game::running() const
{
	// Renvoie l'etat 
	return this->device->run();
}

bool Game::isWindowActive() const
{
	// Renvoie l'etat de la fenetre
	return this->device->isWindowActive();
}