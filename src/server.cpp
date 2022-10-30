#include "server/server.hpp"
#include <csignal>

Server* server;

/**
 * @brief Kill server and free resources
 */
void kill(int)
{
    server->kill();
    delete server;
    exit(0);
}

/**
 * @brief Main function for the server
 */
int main()
{
    server = new Server();

    std::signal(SIGINT, kill);
    std::signal(SIGTERM, kill);
    std::signal(SIGHUP, kill);

    server->run();

    return 0;
}
