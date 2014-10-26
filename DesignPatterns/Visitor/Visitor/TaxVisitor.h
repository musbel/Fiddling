//
//  TaxVisitor.h
//  patterns
//
//  Created by Orn Gunnarsson on 11/09/2014.
//
//

#ifndef __patterns__TaxVisitor__
#define __patterns__TaxVisitor__

#include <iostream>

#include "Visitor.h"
#include "Necessity.h"

class TaxVisitor : public Visitor
{
public:
    TaxVisitor( double tax );
    
    double visit( Necessity& item );
    
private:
    double tax;
};

#endif /* defined(__patterns__TaxVisitor__) */
