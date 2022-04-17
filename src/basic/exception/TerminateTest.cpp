//
// Created by JackyWoo on 2021/11/12.
//

#include <cstdlib>
#include <exception>
#include <iostream>
#include <csignal>
#include <thread>

using namespace std;

void myTerminateHandler()
{
    std::cout << "terminate handler called\n";
    abort(); // forces abnormal termination
}

inline void mySignalHandler(int signo)
{
    std::cout << "signal handler called\n";
    switch (signo)
    {
        case SIGABRT:
            cout << "catch signal 6" << endl;
            break;
        case SIGTERM:
            cout << "catch signal SIGTERM" << endl;
            break;
        case SIGILL:
            cout << "catch signal SIGILL" << endl;
            break;
        case SIGKILL:
            cout << "catch signal 9" << endl;
            break;
        case SIGSEGV:
            cout << "catch signal 11" << endl;
            break;
        case SIGURG:
            /* Do something */
            break;
        case SIGUSR1:
        case SIGUSR2:
            /* Do something */
            break;
        default:
            break;
    }
}

int main()
{
    std::set_terminate(myTerminateHandler);

    signal(SIGABRT, mySignalHandler);
    signal(SIGTERM, mySignalHandler);
    signal(SIGILL, mySignalHandler);
    signal(SIGKILL, mySignalHandler);
    signal(SIGSEGV, mySignalHandler);
    signal(SIGINT, mySignalHandler);

    std::this_thread::sleep_for(std::chrono::seconds (50));

    cout << "end sleep" <<endl;

//    throw 0; // unhandled exception: calls terminate handler
    cout << "program end" << endl;
}