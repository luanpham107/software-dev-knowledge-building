# Chap1. Introduction

## 1.1 What is concurrency in computer system

Context switching

## 1.2 C++ with concurrency
Consider to use concurrency for your application or not.\
Concurrency will help Increase performance\
But also Increase complexity.

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
                            // join will cause the calling thread to wait for the thread associated to completed
}
```
# Chap2. Managing threads

## 2.1 Basic thread management

### 2.1.1 Lauching a thread

std::thread works with any callable type. So you can pass an instance of a class with a function call operator to std::thread constructor
```
    void do_some_work();
    std::thread my_thread(do_some_work);
```

Or

```
    class background_task {
        public:
            void operator() () const {
                do_something();
                do_something_else();
            }
    };
    background_task f;
    std::thread my_thread(f);
```

### 2.1.2 Waiting a thread to complete

If you need to wait for a thread to complete, you can do this by calling join().
There is api joinable() to check if a thread join able or not.

### 2.1.4 Running threads in the background

Calling detach() on a std::thread obj leave thread run in the background.

## 2.2 Passing arguments to a thread func
```
    void f(int i,std::string const& s);

    # This creates a new thread of execution associated with t, which calls f(3, "Hello")
    std::thread t(f,3,”hello”);
```
Full code:
```
    void f(int i,std::string const& s);
    void oops(int some_param)
    {
    char buffer[1024]; 
    sprintf(buffer, "%i",some_param);
    std::thread t(f,3,buffer); # Using std::string avoids dangling pointer
    t.detach();
    }
```
## 2.3 Transfer ownership of a thread
### Definition:
When transfer owner ship be used:
* you want to write a func that create a thread to run in the background but passes back ownership of new thread to the calling faunction rather than wating it to complete.
* Or you want to do the reverse: create a thread and pass ownership into some function that should wait for it to complete.
In 2 case above, you need to transfer ownership from one place to another.
### How to:
```
    void some_function();
    void some_other_function();
    std::thread t1(some_function);  // new thread is started and associated with t1 
    std::thread t2=std::move(t1);   // Transfer ownership to t2, t1 no longer has an associated thread of execution, thread running some_fuction is now associated with t2
    t1=std::thread(some_other_function); // a new thread started & associated with thread obj. Then transfer ownership to t1. Because it is temorary object, don't need invoke std::move()
    std::thread t3;     // t3 is defaut ctor -> created without any associated thread of execuation.
    t3=std::move(t2);   // t1 is associated with the thread running some_other_function. T2 has no associated thread, t3 -> some_function
    t1=std::move(t3);   // t1 already has associated thread (some_other_function)? -> std::terminate() called to terminate program
```