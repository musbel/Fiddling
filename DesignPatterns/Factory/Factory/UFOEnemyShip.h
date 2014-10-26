//
//  UFOEnemyShip.h
//  Factory
//
//  Created by Orn Gunnarsson on 16/09/2014.
//
//

#ifndef Factory_UFOEnemyShip_h
#define Factory_UFOEnemyShip_h

#include "EnemyShip.h"

class UFOEnemyShip : public EnemyShip
{
public:
    UFOEnemyShip() : EnemyShip( "UFO Enemy Ship", 20.0 ) {}
};

#endif
