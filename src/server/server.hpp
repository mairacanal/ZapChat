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

int MAX_MESSAGE_SIZE = 256 ;
int PORT = 4040;
int MAX_CONNECTIONS = 10;


class Server {
    private:
        std::vector<int> connections;
        Socket *serverSocket;
        struct sockaddr_in serverAddr;
        bool isRunning;


    public:
        void Setup();
        void ThreadHandlerRoutine();
        Server(std::string configFilePath);
        void Run();
        void ClientHandlerLoop(int currConnectionFileDescriptor);
};
