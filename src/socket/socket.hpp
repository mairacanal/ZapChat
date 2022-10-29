#pragma once
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <stdexcept>
#include <string>

class Socket {
    private:
        int fd;
        struct sockaddr_in socketAddr;
        int maxConnections;
    public:
        Socket(std::string address, unsigned int port);

        ~Socket();
        //Bind, listen, connect, accept

        void bind();
        void listen();
        bool accept(int &targetFileDescriptor);
        void connect();
        void closed();
        int getFd();
};
