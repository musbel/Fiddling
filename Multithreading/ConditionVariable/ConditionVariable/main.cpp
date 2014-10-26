//
//  main.cpp
//  ConditionVariable
//
//  Created by Orn Gunnarsson on 28/09/2014.
//  Copyright (c) 2014 Orn Gunnarsson. All rights reserved.
//

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::condition_variable cv;
bool ready = false;
int current = 0;

void printNum( int id, int numThreads )
{
    std::unique_lock<std::mutex> lock( mutex );
    
    // Each thread waits until it's their turn, indicated by the wait function
    // which returns true when they should acquire the unique lock and do their
    // thing. If we remove the turn flag we still get a valid behaviour but the
    // order will be random.
    cv.wait( lock, [id]() { return ( id == current && ready ); } );
    
    current++;
    
    std::cout << "Thread [" << id << "]: Current count = " << current << std::endl;
    std::cout << "Thread ID = " << std::this_thread::get_id() << std::endl;
    
    // Notify other threads to check if it is their turn
    cv.notify_all();
}

void run()
{
    std::unique_lock<std::mutex> lock( mutex );
    ready = true;
    cv.notify_all();
}

int main( int argc, const char * argv[] )
{
    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    
    for ( int id = 0; id < numThreads; ++id )
    {
        threads.push_back( std::thread( printNum, id, numThreads ) );
    }
    
    std::cout << "Running " << numThreads << " threads in parallel" << std::endl;
    
    run();
    
    for ( auto& thread : threads )
    {
        thread.join();
    }
    
    return 0;
}
