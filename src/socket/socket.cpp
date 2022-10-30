/**
 * @file socket.cpp
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

#include "socket.hpp"

/**
 * @brief Construct a new Socket:: Socket object
 *
 * @param port Port that the socket is created
 */
Socket::Socket(unsigned int port)
{
    fd = socket(PF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto);

    // Criação do socket retorna -1 caso não tenha sido efetuada corretamente
    try {
        if (fd == -1)
            throw std::runtime_error("Socket's Error");
    } catch (std::runtime_error err) {
        std::cout << "Socket's Error";
        exit(0);
    }

    std::memset(&socketAddr, 0, sizeof(socketAddr));

    // Address format
    socketAddr.sin_family = AF_INET;

    // The socket accepts connections to all the IPs
    socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Set port
    socketAddr.sin_port = htons(port);
}

/**
 * @brief Destroy the Socket:: Socket object
 *
 */
Socket::~Socket()
{
    ::close(fd);
}

/**
 * @brief Estabilish a bind
 *
 */
void Socket::bind()
{
    int set_true = 1;

    // Verify bind
    if (!::bind(fd, (struct sockaddr*)&socketAddr, sizeof(socketAddr)))
        return;

    // Verify the behavior of socket's option
    try {
        if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &set_true, sizeof set_true) != -1)
            return;
        throw std::runtime_error("Bind's Error");
    } catch (std::runtime_error err) {
        std::cout << "Bind's Error";
        exit(0);
    }
}

/**
 * @brief Start the socket listen process
 *
 */
void Socket::listen()
{
    try {
        if (::listen(fd, MAX_CONNECTIONS) == -1)
            throw std::runtime_error("Listen's Error");
    } catch (std::runtime_error err) {
        std::cout << "Listen's Error";
        exit(0);
    }
}

/**
 * @brief Return a boolean that is true if the accept process ocurred
 *
 * @param targetFileDescriptor Value of the file descriptor for the client
 * @return true if the socket accepts the connection
 * @return false if the socket does not accepts the connection
 */
bool Socket::accept(int& targetFileDescriptor)
{
    struct sockaddr_storage theirAddr;

    socklen_t addrSize = sizeof theirAddr;

    // Get a fileDescriptor for the client
    targetFileDescriptor = ::accept(fd, (struct sockaddr*)&theirAddr, &addrSize);
    return targetFileDescriptor == -1 ? false : true;
}

/**
 * @brief Estabilish connection
 *
 * @return int 0 -> Success; -1 -> Error
 */
int Socket::connect()
{
    try {
        if (::connect(fd, (struct sockaddr*)&socketAddr, sizeof(socketAddr)) == -1) {
            throw std::runtime_error("Connection's Error");
        }
    } catch (std::runtime_error error) {
        return -1;
    }
    return 0;
}

/**
 * @brief Verify both send and receive processs and shutdown the socket
 *
 */
void Socket::close()
{
    try {
        if (shutdown(fd, 2) == -1)
            throw std::runtime_error("Socket's Shutdown Error");
    } catch (std::runtime_error err) {
        std::cout << "Sockets error";
        exit(0);
    }
}

/**
 * @brief Return file descriptor
 *
 * @return int value of the file descriptor
 */
int Socket::get_fd()
{
    return fd;
}
