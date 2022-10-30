#include "socket.hpp"

//Create a Socket based on the Port
Socket::Socket(unsigned int port)
{
    fd = socket(PF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto);

    // Criação do socket retorna -1 caso não tenha sido efetuada corretamente
    if (fd == -1)
        throw std::runtime_error("Erro na criação do socket");

    std::memset(&socketAddr, 0, sizeof(socketAddr));

    socketAddr.sin_family = AF_INET;//Address format
    socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);//The socket accepts connections to all the IPs
    socketAddr.sin_port = htons(port);//Set port
}

Socket::~Socket()
{
    ::close(fd);
}

//Estabilish a bind
void Socket::bind()
{
    int set_true = 1;

    //Verify bind
    if (!::bind(fd, (struct sockaddr*)&socketAddr, sizeof(socketAddr)))
        return;

    //Verify the behavior of socket's option
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &set_true, sizeof set_true) != -1)
        return;

    throw std::runtime_error("Bind's Error");
}

//Start the socket listen process
void Socket::listen()
{
    if (::listen(fd, MAX_CONNECTIONS) == -1)
        throw std::runtime_error("Listen's Error");
}

//Return a boolean that is true if the accept process ocurred
bool Socket::accept(int& targetFileDescriptor)
{
    struct sockaddr_storage theirAddr;//Socket of connection

    socklen_t addrSize = sizeof theirAddr;
    targetFileDescriptor = ::accept(fd, (struct sockaddr*)&theirAddr, &addrSize); //Get a fileDescriptor for the client
    return targetFileDescriptor == -1 ? false : true;
}

//Estabilish connection
void Socket::connect()
{
    if (::connect(fd, (struct sockaddr*)&socketAddr, sizeof(socketAddr)) == -1)
        throw std::runtime_error("Connection's Error");
}

//Verify both send and receive processs and shutdown the socket
void Socket::close()
{
    if (shutdown(fd, 2) == -1)
        throw std::runtime_error("Socket's Shutdown Error");
}

//Return file descriptor
int Socket::getFd()
{
    return fd;
}
