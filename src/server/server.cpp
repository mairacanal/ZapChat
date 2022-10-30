#include "server.hpp"

#include <algorithm>
#include <iostream>

constexpr int MAX_MESSAGE_SIZE = 256;
constexpr int PORT = 4040;

Server::Server()
{
    serverSocket = new Socket(std::string(""), PORT);
}

void Server::threadHandler()
{
    int fd;

    if (isRunning && !serverSocket->accept(fd)) {
        return;
    }

    connections.push_back(fd);
    std::thread clientThread(&Server::clientHandler, this, fd);
    clientThread.detach();
}

void Server::setup()
{
    serverSocket->bind();
    serverSocket->listen();
}

void Server::clientHandler(int fd)
{
    send(fd, "Connection succeed", MAX_MESSAGE_SIZE, 0);
    std::cout << "Initializing connection with client" << fd << std::endl;

    int receivedBytes;

    while (isRunning) {
        char message[MAX_MESSAGE_SIZE];
        std::memset(&message, 0, MAX_MESSAGE_SIZE);

        receivedBytes = recv(fd, message, MAX_MESSAGE_SIZE, 0);

        if (receivedBytes == -1) break;

        std::cout << "From client " << fd << ": " << message << std::endl;

        for (auto client : connections) {
            send(client, message, MAX_MESSAGE_SIZE, 0);
            std::cout << "To client " << client << ": " << message << std::endl;
        }
    }

    connections.erase(std::remove(connections.begin(), connections.end(), fd), connections.end());
    std::cout << "Closing connection to client " << fd << std::endl;
    close(fd);
}

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

void Server::run()
{
    isRunning = true;
    setup();

    while (isRunning)
        threadHandler();
}
