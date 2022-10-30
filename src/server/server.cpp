#include "server.hpp"
#include <algorithm>
#include <iostream>

/**
 * @brief Construct a new Server:: Server object
 *
 */
Server::Server()
{
    serverSocket = new Socket(PORT);
}

/**
 * @brief When the server is running, add new connections to the vector of connections
 *
 */
void Server::thread_handler()
{
    int fd;

    if (isRunning && !serverSocket->accept(fd))
        return;

    connections.push_back(fd);
    std::thread clientThread(&Server::client_handler, this, fd);
    clientThread.detach();
}

/**
 * @brief Set up the server connection by the bind and listen
 *
 */
void Server::setup()
{
    serverSocket->bind();
    serverSocket->listen();
}

/**
 * @brief Generate a log when the connection is successful and start the loop for receive new messages and foward/broadcast them
 *
 * @param fd client id
 */
void Server::client_handler(int fd)
{
    send(fd, "Connection succeed", MAX_MESSAGE_SIZE, 0);
    std::cout << "Initializing connection with client " << fd << std::endl;

    int receivedBytes;

    while (isRunning) {
        char message[MAX_MESSAGE_SIZE];
        std::memset(&message, 0, MAX_MESSAGE_SIZE);

        receivedBytes = recv(fd, message, MAX_MESSAGE_SIZE, 0);

        if (receivedBytes <= 0)
            break;

        std::cout << "From client " << fd << ": " << message << std::endl;

        // For every client connected, foward the message
        for (auto client : connections) {
            send(client, message, MAX_MESSAGE_SIZE, 0);
            std::cout << "To client " << client << ": " << message << std::endl;
        }
    }

    connections.erase(std::remove(connections.begin(), connections.end(), fd), connections.end());
    std::cout << "Closing connection to client " << fd << std::endl;
    close(fd);
}

/**
 * @brief Set the bool of running to false to shutdown the server
 *
 */
void Server::kill()
{
    isRunning = false;

    for (auto client : connections) {
        send(client, "Closing server", MAX_MESSAGE_SIZE, 0);
        close(client);
    }

    std::cout << "Closing server" << std::endl;
    serverSocket->close();
    delete serverSocket;
}

/**
 * @brief Initialize the server and main loop
 *
 */
void Server::run()
{
    isRunning = true;
    setup();

    // While the server is running, handle the connections and send/receive process
    while (isRunning)
        thread_handler();

    isRunning = false;
}
