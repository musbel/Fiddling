//
//  Visitor.h
//  patterns
//
//  Created by Orn Gunnarsson on 11/09/2014.
//
//

#ifndef patterns_Visitor_h
#define patterns_Visitor_h

class Necessity;

class Visitor
{
public:
    virtual double visit( Necessity& item ) = 0;
};

#endif
