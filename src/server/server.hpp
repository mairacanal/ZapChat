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




class Server {
    private:
        std::vector<int> connections;
        Socket *serverSocket;
        struct sockaddr_in serverAddr;
        bool isRunning;


    public:
        void Setup();
        void ThreadHandlerRoutine();
        Server();
        void Run();
        void Kill();
        void ClientHandlerLoop(int currConnectionFileDescriptor);
};
