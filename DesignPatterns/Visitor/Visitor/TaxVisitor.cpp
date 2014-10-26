//
//  TaxVisitor.cpp
//  patterns
//
//  Created by Orn Gunnarsson on 11/09/2014.
//
//

#include "TaxVisitor.h"

TaxVisitor::TaxVisitor( double tax ) : tax( tax )
{
}

double TaxVisitor::visit( Necessity& item )
{
    std::cout << "Necessity item - Price with tax" << std::endl;
    return item.getPrice() * tax + item.getPrice();
}