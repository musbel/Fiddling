//
//  main.cpp
//  Synchronisation
//
//  Created by Orn Gunnarsson on 28/09/2014.
//  Copyright (c) 2014 Orn Gunnarsson. All rights reserved.
//

#include <iostream>
#include <vector>
#include <thread>

/*
 
 Demonstrating race conditions using a simple counter and how to address the problem using 
 thread-safe and atomic counters.
 
 How can a simple increment go wrong when multiple threads are accessing the same resource?
 Imagine if two or more threads are executing the increment on the same instance of the
 Counter class. There is no way to know when the operating system switches between the two
 threads. The code in increment which adds 1 to the counter is not an atomic instruction
 (except in the atomic counter). Rather, it is executed as a set of smaller instructions,
 something like:
 
   1. Read the current value into a register
   2. Increment/add value to the register
   3. Write from the register to the memory
 
 Let's say that two threads increment by 5 so we expect to see a final value of 10 in the
 counter. However, if the thread execution is interleaved this is not guaranteed. E.g. if
 thread B reads the value into its register before thread A has copied its own increment
 back from its register, both threads A and B will override the counter value with the same
 value. This is highlighted in the breakdown below:
 
   counter = 0
 
   A:  Reads counter into a register (0)
   B:  Reads counter into a register (0)
   B:  Adds value 1 to register (increment by 1)
   B:  Writes register value (1) back to memory. counter is now 1
   A:  Adds value 1 to register (increment by 1)
   A:  Writes register value (1) back to memory. counter is still 1!
 
 */

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
    
    int numThreads = std::thread::hardware_concurrency();

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
//        std::thread deadlockThread( [&counter]() { counter.both(); } );
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
    
    // -- Atomic test --
    {
        AtomicCounter counter;
        incrementCounter( counter, 1000 );
        std::cout << "AtomicCounter value: " << counter.get() << std::endl;
    }

    // -- Atomic for thread safety --
    {
        AtomicCounter counter;
        std::vector<std::thread> threads;
        
        for ( int i = 0; i < numThreads; ++i )
        {
            threads.push_back( std::thread( incrementCounter<AtomicCounter>, std::ref( counter ), 100 ) );
        }
        
        for ( int i = 0; i < numThreads; ++i )
        {
            threads[i].join();
        }
        
        std::cout << "AtomicCounter value (" << numThreads << " threads): " << counter.get() << std::endl;
    }
    
    return 0;
}
