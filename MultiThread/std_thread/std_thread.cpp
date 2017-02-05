///////////////////////////////////////////////////////////////////////
// std_thread.cpp - demo of std::thread library                      //
// ver 1.0                                                           //
// Language:    C++                                                  //
// Author: Cunyang Shui                                              //
///////////////////////////////////////////////////////////////////////
//
// demo of std::thread
//   1. globle function with or without argument.
//   2. class member function create thread call own private member function
//      with or without argument.
//   3. difference between join() and detach().
//

#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>

std::mutex _x; // protect output stream in each thread

class MyClass{
public:
    MyClass(){}
    ~MyClass(){}
    
    //----< memberFunc() call two private functions in seperate thread >----
    void memberFunc(){
        _x.lock();
        std::cout << "class member function called" << std::setw(17)
                  << "thread id: " << std::this_thread::get_id() << std::endl;
        _x.unlock();
        std::thread t1(&MyClass::helper1, this);    //"this" here is the current instance of this class
        std::thread t2(&MyClass::helper2, this, 44, 55);
        t1.detach();
        t2.detach();
    }
private:
    void helper1(){
        _x.lock();
        std::cout << "member1 with no arg" << std::setw(26)
                  << "thread id: " << std::this_thread::get_id() << std::endl;
        _x.unlock();
    }
    void helper2(int arg1, int arg2){
        _x.lock();
        std::cout << "member2 with arg1: " << arg1 << ", arg2: " << arg2 << std::setw(14)
                  << "thread id: " << std::this_thread::get_id() << std::endl;
        _x.unlock();
    }
};

//----< globle function with no argument >----
void glbfunc1(){
    _x.lock();
    std::cout << "child1 with no arg" <<  std::setw(27)
              << "thread id: " << std::this_thread::get_id() << std::endl;
    _x.unlock();
}

//----< globle function with one argument >----
void glbfunc2(int number){
    _x.lock();
    std::cout << "child2 with arg:  " << number << std::setw(25)
              << "thread id: " << std::this_thread::get_id() << std::endl;
    _x.unlock();
}

//----< globle function with multiple arguments >----
void glbfunc3(int number1, int number2){
    _x.lock();
    std::cout << "child3 with arg1: " << number1 << ", arg2: " << number2 << std::setw(15)
              << "thread id: " << std::this_thread::get_id() << std::endl;
    _x.unlock();
}

int main()
{
    std::cout << "\n\n";
    _x.lock();
    std::cout << "main thread" << std::setw(34)
              << "thread id: " << std::this_thread::get_id() << std::endl;
    _x.unlock();
    std::thread t1(glbfunc1);          //new thread with function and no argument
    std::thread t2(&glbfunc2, 11);     //new thread with function and one argument
    std::thread t3(glbfunc3, 22, 33);  //new thread with function and multiple argument

    
    MyClass myObj;
    myObj.memberFunc(); // my object call member function, which create 2 thread running MyClass private function
    
    t1.join();
    t2.join();
    t3.join();
    
    std::thread t4([](){ while(1) std::cout << "lambda" << std::endl; });
    //t4.join();
    t4.detach(); // if I use t4.join() here, this thread will be run forever, and main will never exit.
    std::cout << "\n\n";
    return 0;
}

// -- join() and detach()
/*
When thread::join() is called, the calling thread will block until the thread of execution has completed. Basically, this is one mechanism that can be used to know when a thread has finished. When thread::join() returns, the OS thread of execution has completed and the C++ thread object can be destroyed.

The thread::detach() is called, the thread of execution is "detached" from the thread object and is no longer represented by a thread object - they are two independent things. The C++ thread object can be destroyed and the OS thread of execution can continue on. If the program needs to know when that thread of execution has completed, some other mechanism needs to be used. join() cannot be called on that thread object any more, since it is no longer associated with a thread of execution.
 
 for example: my last thread t4, is a lambda expression running forever. If I use t4.join(), main() will exit untill t4 end, but here t4 will never stop. If I use t4.detach(), main() has been lose control of t4, so main() can exit normally. When main thread return, this process will be end, and all thread belonds to this process will be end, includes t4.
*/