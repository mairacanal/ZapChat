#include "server/server.hpp"
#include <csignal>
#include <iostream>
Server* server;

void Kill(int) {
    server->Kill();
    delete server;
    exit(0);
}

Server* server;
int main() {
    server = new Server();
    std::signal(SIGINT, Kill);
    std::signal(SIGTERM, Kill);
    std::signal(SIGHUP, Kill);
    server->Run();
    return 0;
}
