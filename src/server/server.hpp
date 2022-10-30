#pragma once

#include <cstring>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include "../socket/socket.hpp"

/**
 * @brief Server class.
 * 
 */
class Server {
private:
    std::vector<int> connections;
    Socket* serverSocket;
    struct sockaddr_in serverAddr;
    bool isRunning;

    void setup();

    void thread_handler();

    void client_handler(int);

public:
    Server();

    void run();

    void kill();
};
