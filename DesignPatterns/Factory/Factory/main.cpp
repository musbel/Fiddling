//
//  main.cpp
//  Factory
//
//  Created by Orn Gunnarsson on 16/09/2014.
//
//

#include <iostream>
#include <string>

#include "EnemyShipFactory.h"

using namespace std;

int main( int argc, const char * argv[] )
{
    EnemyShipFactory factory;
    
    unique_ptr<EnemyShip> ship;
    
    string shipType;
    cout << "Select ship: ";
    getline( cin, shipType );
    
    ship = factory.makeEnemyShip( shipType );
    
    if ( ship )
    {
        ship->display();
        ship->followHeroShip();
        ship->shoot();
    }
    else
    {
        cout << "Ship " << shipType << " does not exist.\n";
    }
    
    return 0;
}

