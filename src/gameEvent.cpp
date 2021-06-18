#include "gameEvent.hpp"

// COnstructeur
MyEventReceiver::MyEventReceiver()
{
    this->initStateKeys();
}

// Destructeur
MyEventReceiver::~MyEventReceiver()
{

}

// Fonctions
void MyEventReceiver::initStateKeys()
{
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        this->KeyIsDown[i] = false;

    leftButtonDown = false;
    rightButtonDown = false;
}

bool MyEventReceiver::OnEvent(const SEvent& event)
{
    switch (event.EventType)
    {
        case EET_KEY_INPUT_EVENT:
        {
                this->KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
                break;
        }

        case  EET_MOUSE_INPUT_EVENT:
        {
            switch(event.MouseInput.Event)
            {
                case EMIE_LMOUSE_PRESSED_DOWN:
                    this->leftButtonDown = true;
                    break;

                case EMIE_LMOUSE_LEFT_UP:
                    this->leftButtonDown = false;
                    break;

                case EMIE_RMOUSE_PRESSED_DOWN:
                    this->rightButtonDown = true;
                    break;

                case EMIE_RMOUSE_LEFT_UP:
                    this->rightButtonDown = false;
                    break;

                default:
                    break;
            }
        }

        default:
            break;

    }

    return false;
}


// Accesseurs

bool MyEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return this->KeyIsDown[keyCode];
}


bool MyEventReceiver::getLeftButton(void) const
{
    return this->leftButtonDown;
}

bool MyEventReceiver::getRightButton(void) const
{
    return this->rightButtonDown;
}
