//
//  VatVisitor.h
//  patterns
//
//  Created by Orn Gunnarsson on 11/09/2014.
//
//

#ifndef __patterns__VatVisitor__
#define __patterns__VatVisitor__

#include <iostream>

#include "Visitor.h"
#include "Necessity.h"

class VatVisitor : public Visitor
{
public:
    VatVisitor( double vat );
    
    double visit( Necessity& item );
    
private:
    double vat;
};

#endif /* defined(__patterns__VatVisitor__) */
