#pragma once

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

/**
 * @brief Class for the socket
 *
 */
class Socket {
private:
    static constexpr int MAX_CONNECTIONS = 10;
    int fd;
    struct sockaddr_in socketAddr;

public:
    Socket(unsigned int port);

    ~Socket();
    // Bind, listen, connect, accept

    void bind();
    void listen();
    bool accept(int& targetFileDescriptor);
    int connect();
    void close();
    int get_fd();
};
