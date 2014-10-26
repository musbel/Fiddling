//
//  Necessity.h
//  patterns
//
//  Created by Orn Gunnarsson on 11/09/2014.
//
//

#ifndef __patterns__Necessity__
#define __patterns__Necessity__

#include <iostream>
#include "Visitable.h"

class Necessity : public Visitable
{
public:
    Necessity( double price );
    
    double getPrice() const;
    double accept( Visitor& visitor );
    
private:
    double price;
};

#endif /* defined(__patterns__Necessity__) */
