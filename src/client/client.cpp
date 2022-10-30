#include "client.hpp"
#include "../gtk/window/window.hpp"

// Client constructor class
Client::Client(int port, int maxMessageSize, std::string user)
    : maxMessageSize { maxMessageSize }
    , port { port }
    , user { user }
    , message {}
    , mutex {}
{
    socket = new Socket(port);
}

void Client::Connect(char* message)
{
    std::string connected = user + " joined the chat!";
    connected.resize(maxMessageSize); // Setup the message for the maxsize
}

void Client::Disconnect()
{
    std::string discMsg = "Tchauzinho";
    send(socket->getFd(), discMsg.data(), discMsg.size(), 0);
}

void Client::send_message(Glib::ustring message) const
{
    message.resize(maxMessageSize);
    send(socket->getFd(), (const void*)message.c_str(), message.size(), 0);
}

// Destroy Client
Client::~Client()
{
    delete socket;
}

void Client::run(Window* caller)
{
    {
        Glib::Threads::Mutex::Lock lock(mutex);
        isRunning = true;
        this->message = "";
    }

    socket->connect();
    char initialMessage[maxMessageSize];

    // lê a mensagem inicial do servidor
    read(socket->getFd(), initialMessage, sizeof(initialMessage));
    Connect(initialMessage);

    // loop principal de comunicação
    while (isRunning) {
        char message[maxMessageSize];
        Glib::Threads::Mutex::Lock lock(mutex);

        if (recv(socket->getFd(), message, maxMessageSize, 0) <= 0) {
            raise(SIGTERM);
            break;
        }

        this->message = std::string { message };

        lock.release();
        caller->notify();
    }

    isRunning = false;
}

void Client::get_message(Glib::ustring* message) const
{
    if (message)
        *message = this->message;
}

bool Client::has_stopped() const
{
    return !isRunning;
}
