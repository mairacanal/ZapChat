#include "socket.hpp"
#include <iostream>

Socket::Socket(std::string address, unsigned int port){
    fd = socket(PF_INET, SOCK_STREAM, getprotobyname("tcp") -> p_proto);
    
    //Criação do socket retorna -1 caso não tenha sido efetuada corretamente
    if(fd == -1)
        throw std::runtime_error("Erro na criação do socket");
    std::memset(&socketAddr, 0, sizeof(socketAddr));

    socketAddr.sin_family = AF_INET; 
    socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socketAddr.sin_port = htons(port);
    maxConnections = 10;
}

Socket::~Socket(){
   // close();
}

void Socket::bind(){
    int option = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option) == 0)
        if (::bind(fd, (struct sockaddr *)&socketAddr, sizeof(socketAddr)) == 0)
            return;
    
    throw std::runtime_error("Erro no Bind");
    
}

void Socket::listen(){
    if(::listen(fd, maxConnections) == -1)
        throw std::runtime_error("Erro ao iniciar o Listen");
}

bool Socket::accept(int &targetFileDescriptor){
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof their_addr;
    targetFileDescriptor = ::accept(fd, (struct sockaddr *)&their_addr, &addr_size);
    return targetFileDescriptor == -1 ? false : true;
}

void Socket::connect(){
    if(::connect(fd, (struct sockaddr *)&socketAddr, sizeof(socketAddr)) == -1)
        throw std::runtime_error("Erro ao iniciar a conexão");
}

void Socket::closed(){
    if(shutdown(fd, 2) == -1)
        throw std::runtime_error("Erro ao fechar o socket");
    
}

int Socket::getFd(){
    return fd;
}
