#pragma once

#include <csignal>
#include <mutex>
#include <sstream>
#include <iostream>

#include "../socket/socket.hpp"

class Client {
private:
    int port;
    bool isRunning;
    std::string address;
    std::string user;
    Socket* ClientSocket;
    static Client* instance;
    static std::mutex mutex;

public:
    int maxMessageSize;
    Client(int port, int maxMessageSize, std::string address, std::string user);
    void Receive(char* message);
    void Connect(char* message);
    static Client* GetInstance();
    static Client* GetInstance(int port, int maxMessageSize, std::string address, std::string user);
    void Disconnect();
    void SendMessage(std::string message);
    void Run();
    ~Client();
};
