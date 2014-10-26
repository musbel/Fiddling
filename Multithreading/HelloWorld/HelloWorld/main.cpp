//
//  main.cpp
//  HelloWorld
//
//  Created by Orn Gunnarsson on 13/09/2014.
//
//

#include <iostream>
#include <thread>

using namespace std;

void hello( const string& name, int num )
{
    cout << "Hello Concurrent " << name << " number " << num << "\n";
}

int main( int argc, char *argv[] )
{
    thread t( hello, "Bob", 10 );
    t.join();
    
    return 0;
}