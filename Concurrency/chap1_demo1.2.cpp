#include <iostream>
// #include <thread>
#include "mingw.thread.h"

// Start of 2nd thread
void hello() {
    std::cout <<"Hello in thread";
}

// Start of initial thread (or 1st thread)
int main() {
    std::thread t(hello);   // new thread has bene launched, the initial thread continue executions
    t.join();               // if not call this, program execute to end of main. So that end of program.
                            // join will cause the calling thread to wait for the thread associated t
}