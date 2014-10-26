//
//  main.cpp
//  patterns
//
//  Created by Orn Gunnarsson on 11/09/2014.
//
//

#include <iostream>

#include "Necessity.h"
#include "TaxVisitor.h"
#include "VatVisitor.h"

int main( int argc, const char * argv[] )
{
    Necessity milk( 0.84 );
    
    TaxVisitor necessityTax( 0.1 );
    std::cout << "Taxed milk price = " << milk.accept( necessityTax ) << std::endl;
    
    VatVisitor vat( 0.2 );
    std::cout << "Milk VAT = " << milk.accept( vat ) << std::endl;
    
    return 0;
}

