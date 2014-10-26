//
//  Visitable.h
//  patterns
//
//  Created by Orn Gunnarsson on 11/09/2014.
//
//

#ifndef patterns_Visitable_h
#define patterns_Visitable_h

#include "Visitor.h"

class Visitable
{
public:
    virtual double accept( Visitor& visitor ) = 0;
};

#endif
