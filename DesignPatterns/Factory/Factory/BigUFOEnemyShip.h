//
//  BigUFOEnemyShip.h
//  Factory
//
//  Created by Orn Gunnarsson on 17/09/2014.
//
//

#ifndef Factory_BigUFOEnemyShip_h
#define Factory_BigUFOEnemyShip_h

#include "UFOEnemyShip.h"

class BigUFOEnemyShip : public EnemyShip
{
public:
    BigUFOEnemyShip() : EnemyShip( "Big UFO Enemy Ship", 40.0 ) {}
};

#endif
