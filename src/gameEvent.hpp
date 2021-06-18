#ifndef __GAMEEVENT__
#define __GAMEEVENT__

#include "librairies.hpp"

class MyEventReceiver : public IEventReceiver
{

    // Variables 
    bool KeyIsDown[KEY_KEY_CODES_COUNT];     // l'etat du bouton pressé
    bool leftButtonDown;
    bool rightButtonDown;

    // Fonctions
    void initStateKeys();
    
public:
    // Constructeurs
    MyEventReceiver();

    // Destructeur
    ~MyEventReceiver();


    // Fonctions 
    virtual bool OnEvent(const SEvent& event);
    
    // Accesseurs
    virtual bool IsKeyDown(EKEY_CODE keyCode) const;
    bool getLeftButton(void) const;
    bool getRightButton(void) const;
    
};

#endif