#include "client.hpp"
#include "../socket/socket.hpp"

// Static class variables
Client* Client::instance { nullptr };
std::mutex Client::mutex;

// Instantiating the client
Client* Client::GetInstance(int port, int maxMessageSize, std::string user)
{
    std::lock_guard<std::mutex> lock(mutex);
    //Create the instance of client and return it
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

// Client constructor class
Client::Client(int port, int maxMessageSize, std::string user)
    : maxMessageSize { maxMessageSize }
    , port { port }
    , user { user }
{
    ClientSocket = new Socket(port);
};

// Main execution system
void Client::Run()
{
    isRunning = true;
    ClientSocket->connect();
    char initialMessage[maxMessageSize];

    // Read the initial message from the server
    read(ClientSocket->getFd(), initialMessage, sizeof(initialMessage));
    Connect(initialMessage);

    // Main communication loop
    while (isRunning) {

        char message[maxMessageSize];//While is running, recive the message of the socket
        if (recv(ClientSocket->getFd(), message, sizeof(message), 0) <= 0) {
            raise(SIGTERM);
            break;
        }
        Receive(message);// Redirect the message for using as API with gtk
    }

    isRunning = false;
}

// Established connection with server
void Client::Connect(char* message)
{
    std::string conected = user + " joined the chat!";
    conected.resize(maxMessageSize);// Setup the message for the maxsize
}

// Message received by client
void Client::Receive(char* message)
{
    printf("%s\n", message);
}

// Disconnecting from server
void Client::Disconnect()
{
    std::string discMsg = "Bye!";
    send(ClientSocket->getFd(), discMsg.data(), discMsg.size(), 0);
}

// Client message sending
void Client::SendMessage(std::string message)
{
    message.resize(maxMessageSize);
    send(ClientSocket->getFd(), (const void*)message.c_str(), message.size(), 0);
}

// Destroy Client
Client::~Client()
{
    delete ClientSocket;
}
