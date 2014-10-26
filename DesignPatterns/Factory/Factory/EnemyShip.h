//
//  EnemyShip.h
//  Factory
//
//  Created by Orn Gunnarsson on 16/09/2014.
//
//

#ifndef Factory_EnemyShip_h
#define Factory_EnemyShip_h

#include <iostream>
#include <string>

using namespace std;

class EnemyShip
{
public:
    EnemyShip( string name, double amountDamage ) : name( name ), amountDamage( amountDamage ) {}
    virtual ~EnemyShip() = 0;
    
    string getName() const { return name; }
    double getAmountDamage() const { return amountDamage; }
    
    void followHeroShip() { cout << getName() << " is following the hero ship.\n"; }
    void display() { cout << getName() << " is on the screen.\n"; }
    void shoot() { cout << getName() << " attacks and does " << getAmountDamage() << " damage.\n"; }
    
private:
    string name;
    double amountDamage;
};

#endif
