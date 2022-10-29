#include "server.hpp"

#include <algorithm>
#include <iostream>

Server::Server(){
    serverSocket = new Socket(std::string(""), PORT);
}

void Server::ThreadHandlerRoutine(){
    int connectionFileDescriptor;
    if (isRunning && !serverSocket->accept(connectionFileDescriptor)) {
        return;
    }

    connections.push_back(connectionFileDescriptor);
    std::thread currClientThread(&Server::ClientHandlerLoop, this, connectionFileDescriptor);
    currClientThread.detach();
}

void Server::Setup(){
    serverSocket->bind();
    serverSocket->listen();
}

void Server::ClientHandlerLoop(int currConnectionFileDescriptor){
    send(currConnectionFileDescriptor, "Conexão recebida com sucesso", MAX_MESSAGE_SIZE , 0);
    printf("Iniciando conexão com o cliente %d\n", currConnectionFileDescriptor);

    int receivedBytes;
    while (isRunning) {
        char message[MAX_MESSAGE_SIZE];
        std::memset(&message, 0, MAX_MESSAGE_SIZE); 


        receivedBytes = recv(currConnectionFileDescriptor, message, MAX_MESSAGE_SIZE, 0);

        if (receivedBytes == -1){
            printf("Erro no recebimento da mensagem!\nAbortando Execução..\n");
            isRunning = false;
            break;
        };

        printf("Recebido do cliente %d: %s\n", currConnectionFileDescriptor, message);

        for (auto client : connections) {
            send(client, message, MAX_MESSAGE_SIZE, 0);
            printf("Enviando para o cliente  %d: %s\n", client, message);
        }
    };
}

void Server::Kill() {
    isRunning = false;
    for (auto client : connections) {
        send(client, "Fechando o servidor", MAX_MESSAGE_SIZE, 0);
        close(client);
    }
}

void Server::Run(){
    isRunning = true;
    Setup();

    while (isRunning){
        ThreadHandlerRoutine();
    }
    
    
}