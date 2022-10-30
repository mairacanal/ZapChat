/**
 * @file server.cpp
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
