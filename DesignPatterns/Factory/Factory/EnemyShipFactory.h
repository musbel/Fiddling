//
//  EnemyShipFactory.h
//  Factory
//
//  Created by Orn Gunnarsson on 16/09/2014.
//
//

#ifndef Factory_EnemyShipFactory_h
#define Factory_EnemyShipFactory_h

#include <memory>
#include <string>

#include "UFOEnemyShip.h"
#include "BigUFOEnemyShip.h"
#include "RocketEnemyShip.h"

using namespace std;

class EnemyShipFactory
{
public:
    unique_ptr<EnemyShip> makeEnemyShip( const string& name )
    {
        if ( name == "U" )
        {
            return unique_ptr<EnemyShip>( new UFOEnemyShip() );
        }
        else if ( name == "B" )
        {
            return unique_ptr<EnemyShip>( new BigUFOEnemyShip() );
        }
        else if ( name == "R" )
        {
            return unique_ptr<EnemyShip>( new RocketEnemyShip() );
        }
        
        return unique_ptr<EnemyShip>();
    }
};

#endif
