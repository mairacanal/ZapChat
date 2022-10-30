#pragma once

/**
 * @file server.hpp
 * @author Felipe de Alcântara Tomé (11800970)
 * @author Francisco Reis Nogueira (11954374)
 * @author Luiz Henrique Pereira (11918539)
 * @author Maíra de Souza Canal (11819403)
 * @author João Augusto Fernandes Barbosa (11953348)
 * @version 0.1
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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
