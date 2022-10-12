# Chap1. Introduction

## 1.1 What is concurrency in computer system

Context switching

## 1.2 C++ with concurrency
Old C++ 1998: Using external libraris from window API or POSIX
C++ 11 already support C++ thread as a standard library. Example:

```
#include <iostream>
#include <thread>

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
```
