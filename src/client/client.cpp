#include "client.hpp"
#include "../socket/socket.hpp"

Client* Client::instance { nullptr };
std::mutex Client::mutex;

Client* Client::GetInstance(int port, int maxMessageSize, std::string user)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
        instance = new Client(port, maxMessageSize, user);

    return instance;
}

Client* Client::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        throw std::runtime_error("The Client has not been initialized");
    }
    return instance;
}

Client::Client(int port, int maxMessageSize, std::string user)
    : maxMessageSize { maxMessageSize }
    , port { port }
    , user { user }
{
    ClientSocket = new Socket(port);
};

void Client::Run()
{
    isRunning = true;
    ClientSocket->connect();
    char initialMessage[maxMessageSize];

    // lê a mensagem inicial do servidor
    read(ClientSocket->getFd(), initialMessage, sizeof(initialMessage));
    Connect(initialMessage);

    // loop principal de comunicação
    while (isRunning) {

        char message[maxMessageSize];
        if (recv(ClientSocket->getFd(), message, sizeof(message), 0) <= 0) {
            raise(SIGTERM);
            break;
        }
        Receive(message);
    }

    isRunning = false;
}

void Client::Connect(char* message)
{
    std::string conected = user + " joined the chat!";
    conected.resize(maxMessageSize);
}

void Client::Receive(char* message)
{
    printf("%s\n", message);
}

void Client::Disconnect()
{
    std::string discMsg = "Bye!";
    send(ClientSocket->getFd(), discMsg.data(), discMsg.size(), 0);
}

void Client::SendMessage(std::string message)
{
    message.resize(maxMessageSize);
    send(ClientSocket->getFd(), (const void*)message.c_str(), message.size(), 0);
}

Client::~Client()
{
    delete ClientSocket;
}
