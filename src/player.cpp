#include "player.hpp"

Player::t = 0;

Player::Player(ISceneManager& smgr, IVideoDriver& driver, ITriangleSelector& selector, SMaterial& material)
{
	this->initVariables();
	this->initPlayer(smgr, driver, selector, material);
	this->initViseur(smgr, driver);
}

Player::~Player()
{
	delete this->nodePlayer;
	delete this->meshPlayer;
}


void Player::initVariables()
{
	this->nodePlayer = nullptr;
	this->meshPlayer = nullptr;
	this->param = 0;
	//playerMaterial = 0;
}

void Player::initPlayer(ISceneManager& smgr, IVideoDriver& driver,ITriangleSelector& selector, SMaterial& material)
{
	this->meshPlayer = smgr.getMesh("data/AK/AK.obj");
	this->nodePlayer = smgr.addAnimatedMeshSceneNode(this->meshPlayer, smgr.getActiveCamera(),
                                          10,
                                          core::vector3df (40, -60, 70));
	this->nodePlayer->setMaterialTexture(0, driver.getTexture("data/AK/AK_diffuse.jpg"));
    this->nodePlayer->setMaterialFlag(EMF_LIGHTING, true);
    this->nodePlayer->setScale(core::vector3df(0.6f));
    this->nodePlayer->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL );
    this->nodePlayer->setMaterialFlag(video::EMF_ZBUFFER, false);
    this->posIni = this->nodePlayer->getPosition();

}

void Player::initViseur(ISceneManager& smgr,IVideoDriver& driver )
{
	// Viseur.
    this->bill = smgr.addBillboardSceneNode();
    this->bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
    this->bill->setMaterialTexture(0, driver.getTexture("media/particle.bmp"));
    this->bill->setMaterialFlag(video::EMF_LIGHTING, false);
    this->bill->setMaterialFlag(video::EMF_ZBUFFER, false);
    this->bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));

    this->bill->setID(0); // This ensures that we don't accidentally ray-pick it

    // Add a light, so that the unselected nodes aren't completely dark.
    this->light = smgr.addLightSceneNode(0, core::vector3df(-60,100,400),video::SColorf(1.0f,1.0f,1.0f,1.0f), 600.0f);
    this->light->setID(ID_IsNotPickable); // Make it an invalid target for selection.

    // Remember which scene node is highlighted
     this->highlightedSceneNode = 0;
     this->collMan = smgr.getSceneCollisionManager();
}

// Fonctions
void Player::update(IVideoDriver& driver,Camera& camera, SMaterial& material, MyEventReceiver& receiver)
{
	this->targetGun(driver, camera, material);
	//this->gunMovementNotMovingState();
	this->updateState(receiver);
    this->updatePlayerMovement();
}

void Player::targetGun(IVideoDriver& driver,Camera& camera, SMaterial& material)
{
    if (this->highlightedSceneNode)
    {
        this->highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, true);
        this->highlightedSceneNode = 0;
    }

    // ray
    core::line3d<f32> ray;
    ray.start = camera.getNode()->getPosition();
    ray.end = ray.start + (camera.getNode()->getTarget() - ray.start).normalize() * 10000.0f;

    // Tracks the current intersection point with the level or a mesh
    core::vector3df intersection;
    // Used to show with triangle has been hit
    core::triangle3df hitTriangle;

    // Intersection
    scene::ISceneNode * selectedSceneNode =
            this->collMan->getSceneNodeAndCollisionPointFromRay(
                ray,
                intersection, // This will be the position of the collision
                hitTriangle, // This will be the triangle hit in the collision
                IDFlag_IsPickable, // This ensures that only nodes that we have
                // set up to be pickable are considered
                0); // Check the entire scene (this is actually the implicit default)

    // If the ray hit anything, move the billboard to the collision position
    // and draw the triangle that was hit.
    if(selectedSceneNode)
    {
        this->bill->setPosition(intersection);

        // We need to reset the transform before doing our own rendering.
        driver.setTransform(video::ETS_WORLD, core::matrix4());
        driver.setMaterial(material);

        // We can check the flags for the scene node that was hit to see if it should be
        // highlighted. The animated nodes can be highlighted, but not the Quake level mesh
        if((selectedSceneNode->getID() & IDFlag_IsHighlightable) == IDFlag_IsHighlightable)
        {
            this->highlightedSceneNode = selectedSceneNode;

            // Highlighting in this case means turning lighting OFF for this node,
            // which means that it will be drawn with full brightness.
            this->highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
        }
    }
}


void Player::notMovingMovement()
{
	this->param++;
    // float f = 1 - exp(-0.01*this->u);
    // std::cout << f << std::endl;
	this->nodePlayer->setPosition(this->posIni + core::vector3df (0, 0.1, 0)* sin(this->param *3* PI/180));
	if (this->param == 360) this->param = 0;
    t--;
}

void Player::targetMovement()
{
    float f = 1 - exp(-0.01*t);
    
    this->nodePlayer->setPosition(this->nodePlayer->getPosition()*(1-f) + f*core::vector3df (1, -30, 50));
    t++;
}

void Player::updateState(MyEventReceiver& receiver)
{
	this->currentState = playerState::NOT_MOVING;
	if(receiver.IsKeyDown(irr::KEY_UP)|| receiver.IsKeyDown(irr::KEY_LEFT) || receiver.IsKeyDown(irr::KEY_RIGHT) || receiver.IsKeyDown(irr::KEY_DOWN))
		this->currentState = playerState::MOVING;
    if(receiver.IsKeyDown(irr::KEY_SPACE))
        this->currentState = playerState::JUMPING;
    if(receiver.getRightButton())
        this->currentState = playerState::TARGET;
    
}

void Player::updatePlayerMovement()
{
    switch(this->currentState)
    {
        case playerState::NOT_MOVING : 
            this->notMovingMovement();
            break;
        case playerState::MOVING : 
            //
            break;
        case playerState::JUMPING : 
            // 
            break;
        case playerState::TARGET : 
            this->targetMovement();
            break;
        default :
            break;

    }
}