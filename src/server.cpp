#include "server/server.hpp"
#include <csignal>
#include <iostream>

Server* server;

void kill(int)
{
    server->kill();
    delete server;
    exit(0);
}

int main()
{
    server = new Server();

    std::signal(SIGINT, kill);
    std::signal(SIGTERM, kill);
    std::signal(SIGHUP, kill);

    server->run();

    return 0;
}
