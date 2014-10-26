//
//  main.cpp
//  Synchronisation
//
//  Created by Orn Gunnarsson on 26/10/2014.
//  Copyright (c) 2014 Orn Gunnarsson. All rights reserved.
//

#include <iostream>
#include <vector>
#include <thread>

struct Counter
{
    int value;
    
    Counter() : value( 0 ) {}
    
    void increment()
    {
        ++value;
    }
    
    void reset()
    {
        value = 0;
    }
};

struct ConcurrentCounter
{
    std::mutex mutex;
    int value;
    
    ConcurrentCounter() : value( 0 ) {}
    
    void increment()
    {
        std::lock_guard<std::mutex> guard( mutex );
        ++value;
    }
    
    void decrement()
    {
        std::lock_guard<std::mutex> guard( mutex );
        --value;
    }
    
    void both()
    {
        // This will cause a deadlock as by definition the
        // mutex can only be locked once by a thread
        std::lock_guard<std::mutex> guard( mutex );
        
        increment();
        decrement();
    }
    
    void reset()
    {
        std::lock_guard<std::mutex> guard( mutex );
        value = 0;
    }
};

struct ConcurrentCounterRecursiveMutex
{
    std::recursive_mutex mutex;
    int value;
    
    std::once_flag flag;    // For call_once test
    
    ConcurrentCounterRecursiveMutex() : value( 0 ) {}
    
    void increment()
    {
        std::lock_guard<std::recursive_mutex> guard( mutex );
        ++value;
    }
    
    void decrement()
    {
        std::lock_guard<std::recursive_mutex> guard( mutex );
        --value;
    }
    
    void both()
    {
        // A recursive mutex will avoid a deadlock as it can be
        // acquired several times by the same thread
        std::lock_guard<std::recursive_mutex> guard( mutex );
        
        increment();
        decrement();
    }
    
    void doSomething()
    {
        // Taco should only be printed once regardless of the number
        // of threads executing this function
        std::call_once( flag, []() { std::cout << "Taco" << std::endl; } );
        
        // Cheese will be printed as many times as there are threads
        std::cout << "Cheese" << std::endl;
    }
};

struct AtomicCounter
{
    std::atomic<int> value;
    
    void increment()
    {
        ++value;
    }
    
    int get()
    {
        return value.load();
    }
};

template<typename T>
void incrementCounter( T& counter, int numIncrements )
{
    for ( int i = 0; i < numIncrements; ++i )
    {
        counter.increment();
    }
}

int main( int argc, const char * argv[] )
{
    // -- Using a mutex to avoid race conditions --
    
    // Single threaded increment which should give a value of 100
    {
        Counter counter;
        incrementCounter( counter, 100 );
        std::cout << "Counter value (main thread): " << counter.value << std::endl;
    }
    
    // Have one thread do the increment using a lambda function, counts to 100
    {
        Counter counter;
        std::thread t( [&counter] () { for ( int i = 0; i < 100; ++i ) { counter.increment(); } } );
        t.join();
        std::cout << "Counter value (single thread): " << counter.value << std::endl;
    }
    
    int numThreads = 6;
    
    // Multi threaded increment which will behave erratically
    {
        Counter counter;
        std::vector<std::thread> threads;
        
        for ( int i = 0; i < numThreads; ++i )
        {
            threads.push_back( std::thread( incrementCounter<Counter>, std::ref( counter ), 100 ) );
        }
        
        for ( int i = 0; i < numThreads; ++i )
        {
            threads[i].join();
        }
        
        std::cout << "Counter value (" << numThreads << " threads): " << counter.value << std::endl;
    }
    
    // Multi threaded increment using a safe concurrent counter
    {
        ConcurrentCounter safeCounter;
        std::vector<std::thread> threads;
        
        for ( int i = 0; i < numThreads; ++i )
        {
            threads.push_back( std::thread( incrementCounter<ConcurrentCounter>, std::ref( safeCounter ), 100 ) );
        }
        
        for ( int i = 0; i < numThreads; ++i )
        {
            threads[i].join();
        }
        
        std::cout << "ConcurrentCounter value (" << numThreads << " threads): " << safeCounter.value << std::endl;
    }
    
    // -- Recursive Mutex --
    // A non-recursive mutex will cause a deadlock here when the thread tries
    // to acquire the lock more than once
    {
        //        ConcurrentCounter counter;
        //        std::thread deadlockThread( [&counter]() { counter(); } );
        //        deadlockThread.join();
        //        std::cout << "This will never be printed due to the deadlock" << std::endl;
    }
    
    // A recursive mutex can acquire the lock several times in the same thread
    // and therefore avoids a deadlock
    {
        ConcurrentCounterRecursiveMutex counter;
        std::thread happyThread( [&counter]() { counter.both(); } );
        happyThread.join();
        std::cout << "Recursive mutex counter has a value of: " << counter.value << std::endl;
    }
    
    // -- Call once --
    // We should see one Taco and several Cheese
    {
        ConcurrentCounterRecursiveMutex counter;
        std::thread t( [&counter]() { for ( int i = 0; i < 10; ++i ) { counter.doSomething(); } } );
        t.join();
    }
    
    // -- Atomic for thread safety --
    {
        AtomicCounter counter;
        incrementCounter( counter, 1000 );
        std::cout << "Counter value (main thread): " << counter.get() << std::endl;
    }
    
    return 0;
}
