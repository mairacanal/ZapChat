#include "socket.hpp"

Socket::Socket(std::string address, unsigned int port)
{
    fd = socket(PF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto);

    // Criação do socket retorna -1 caso não tenha sido efetuada corretamente
    if (fd == -1)
        throw std::runtime_error("Erro na criação do socket");

    std::memset(&socketAddr, 0, sizeof(socketAddr));

    socketAddr.sin_family = AF_INET;
    socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socketAddr.sin_port = htons(port);
}

Socket::~Socket()
{
    ::close(fd);
}

void Socket::bind()
{
    int set_true = 1;

    if (!::bind(fd, (struct sockaddr*)&socketAddr, sizeof(socketAddr)))
        return;

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &set_true, sizeof set_true) != -1)
        return;

    throw std::runtime_error("Erro no Bind");
}

void Socket::listen()
{
    if (::listen(fd, MAX_CONNECTIONS) == -1)
        throw std::runtime_error("Erro ao iniciar o Listen");
}

bool Socket::accept(int& targetFileDescriptor)
{
    struct sockaddr_storage theirAddr;

    socklen_t addrSize = sizeof theirAddr;
    targetFileDescriptor = ::accept(fd, (struct sockaddr*)&theirAddr, &addrSize);
    return targetFileDescriptor == -1 ? false : true;
}

void Socket::connect()
{
    if (::connect(fd, (struct sockaddr*)&socketAddr, sizeof(socketAddr)) == -1)
        throw std::runtime_error("Erro ao iniciar a conexão");
}

void Socket::close()
{
    if (shutdown(fd, 2) == -1)
        throw std::runtime_error("Erro ao fechar o socket");
}

int Socket::getFd()
{
    return fd;
}
