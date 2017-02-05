///////////////////////////////////////////////////////////////////////
// Callables.cpp - Executing Callable Objects                        //
//                                                                   //
// Source: Jim Fawcett, CSE687 - Object Oriented Design              //
///////////////////////////////////////////////////////////////////////
//
// demo of callable object
//


#include <iostream>
#include "../Utilities/Utilities.h"

// function accepting and executing any callable object

template <class CallObj>
void Executor(CallObj& co){
  co();      // invocation of callable object
}
// example callable object - function

void hello(){
  std::cout << "\n  Hello from hello()";
}
// example callable object - functor

class MyFunctor{
public:
  MyFunctor(const std::string& msg) : _msg(msg) {}

  void operator()(){
    std::cout << "\n  " << _msg.c_str() << " from MyFunctor";
  }
private:
  std::string _msg;
};

// example callable object - lambda

std::string msg("Hi again");
std::function<void()> sfun = []() {// dont need copy[=] or capture[&] here, because globle variable will be capture automatically
  std::cout << "\n  " << msg.c_str() << " from std::function bound to lambda"; 
};

using namespace Utilities;
using Utils = StringHelper;

int main(){
  Utils::Title("Demo Executing Callable Objects");

  Executor(hello);
  MyFunctor mf("Hi");
  Executor(mf);
  Executor(sfun);

  // example callable object

  std::string newMsg = "Hi one more time";
    
  std::function<void()> func = [=]() { std::cout << "\n  " << newMsg.c_str() << " from lambda"; };
  Executor(func);
    
//    Executor(
//        [=]() { std::cout << "\n  " << newMsg.c_str() << " from lambda"; }
//    );

  std::cout << "\n\n";

}