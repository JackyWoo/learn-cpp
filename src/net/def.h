//
// Created by wujianchao5 on 2022/6/23.
//

#include <sys/socket.h>

#define LEARN_CPP_DEF_H

#ifndef ECHO_SELECT_DEF_H
#define ECHO_SELECT_DEF_H

#define IPADDRESS "127.0.0.1"
#define PORT 8787
#define MAXLINE     1024
#define LISTENQ 5

static int get_addrin_from_fd(int fd, struct sockaddr_in *addr) {
    auto addrlen = sizeof(struct sockaddr_in);
    bzero(addr, addrlen);
    if (getpeername(fd, (struct sockaddr *) addr, reinterpret_cast<socklen_t *>(&addrlen)) == -1) {
        return -1;
    }
    return 0;
}

#endif //ECHO_SELECT_DEF_H
