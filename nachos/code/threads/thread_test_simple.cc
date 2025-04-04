/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2007-2009 Universidad de Las Palmas de Gran Canaria.
///               2016-2021 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "thread_test_simple.hh"
#include "system.hh"

#include <stdio.h>
#include <string.h>


/// Loop 10 times, yielding the CPU to another ready thread each iteration.
///
/// * `name` points to a string with a thread name, just for debugging
///   purposes.

/// NOTE: The total amount of threads will be N_THREADS + 1 (the "main" thread). 
static const unsigned N_THREADS = 4; 
static const char *threadName[N_THREADS] = {"2nd", "3rd", "4th", "5th"};
static bool done[N_THREADS] = {false};
static void
SimpleThread(void *name_)
{

    // If the lines dealing with interrupts are commented, the code will
    // behave incorrectly, because printf execution may cause race
    // conditions.
    for (unsigned num = 0; num < 10; num++) {
        printf("*** Thread `%s` is running: iteration %u\n", currentThread->GetName(), num);
        currentThread->Yield();
    }
    for (unsigned i = 0; i < N_THREADS; i++) {
        if (strcmp(currentThread->GetName(),threadName[i])==0) {
            done[i] = true;
        }
    }
    printf("!!! Thread `%s` has finished SimpleThread\n", currentThread->GetName());
 
}

/// Set up a ping-pong between several threads.
///
/// Do it by launching one thread which calls `SimpleThread`, and finally
/// calling `SimpleThread` on the current thread.
void
ThreadTestSimple()
{
    Thread *newThreads[N_THREADS];
    for (unsigned i = 0; i < N_THREADS; i++) {
        newThreads[i] = new Thread(threadName[i]);         
        newThreads[i]->Fork(SimpleThread, NULL);
    }

    //the "main" thread also executes the same function
    SimpleThread(NULL);

    //Wait for the new threads to finish if needed
    for (unsigned i = 0; i < N_THREADS; i++) {
        while (!done[i]) {
            currentThread->Yield(); 
        }
    }
    printf("Test finished\n");
}
