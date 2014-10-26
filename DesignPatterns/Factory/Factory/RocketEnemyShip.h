//
//  RocketEnemyShip.h
//  Factory
//
//  Created by Orn Gunnarsson on 16/09/2014.
//
//

#ifndef Factory_RocketEnemyShip_h
#define Factory_RocketEnemyShip_h

#include "EnemyShip.h"

class RocketEnemyShip : public EnemyShip
{
public:
    RocketEnemyShip() : EnemyShip( "Rocket Enemy Ship", 10.0 ) {}
};

#endif
