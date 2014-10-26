//
//  VatVisitor.cpp
//  patterns
//
//  Created by Orn Gunnarsson on 11/09/2014.
//
//

#include "VatVisitor.h"

VatVisitor::VatVisitor( double vat ) : vat( vat )
{
}

double VatVisitor::visit( Necessity& item )
{
    std::cout << "Necessity item - Calculating VAT" << std::endl;
    return item.getPrice() * vat;
}