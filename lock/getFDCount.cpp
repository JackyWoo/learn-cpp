//
// Created by JackyWoo on 2021/10/19.
//

#include <string>
#include <cstdio>
#include <dirent.h>
#include <unistd.h>
#include <iostream>

int getFDCount()
{
    int fd_count;
    char buf[64];

    size_t pid = getpid();
    std::cout<<pid<<std::endl;

#ifdef __linux__
    snprintf(buf, 64, "/proc/%i/fd/", getpid());
#else
    return -1;
#endif

    fd_count = 0;
    DIR *dir = opendir(buf);
    if(!dir)
    {
        std::cout<<buf<<" can not access"<<std::endl;
    }
    while ((readdir(dir)) != nullptr) {
        fd_count++;
    }
    closedir(dir);
    delete dir;
    return fd_count;
}

int main()
{
    std::cout<<getFDCount()<<std::endl;
}