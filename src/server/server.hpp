#pragma once

#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <vector>

#include "../socket/socket.hpp"

/**
 * @brief Server class.
 *
 */
class Server {
private:
    static constexpr int MAX_MESSAGE_SIZE = 256;
    static constexpr int PORT = 4040;

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
