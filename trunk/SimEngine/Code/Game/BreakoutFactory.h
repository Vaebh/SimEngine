#ifndef BREAKOUT_FACTORY_SIMENGINE
#define BREAKOUT_FACTORY_SIMENGINE

#include "../Structure/GameObject.h"

GameObject* CreateBall();
GameObject* CreatePaddle();
GameObject* CreateBlock(Vector3 inPosition);

#endif