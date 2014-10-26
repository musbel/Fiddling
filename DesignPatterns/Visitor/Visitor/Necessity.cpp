//
//  Necessity.cpp
//  patterns
//
//  Created by Orn Gunnarsson on 11/09/2014.
//
//

#include "Necessity.h"

Necessity::Necessity( double price ) : price( price )
{
}

double Necessity::getPrice() const
{
    return price;
}

double Necessity::accept( Visitor& visitor )
{
    return visitor.visit( *this );
}
