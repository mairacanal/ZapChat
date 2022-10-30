#include "client.hpp"
#include "../gtk/window/window.hpp"

// Client constructor class
Client::Client()
    : username { }
    , message {}
    , mutex {}
{
    socket = new Socket(PORT);
}

void Client::connect_client()
{
    Glib::ustring connected = ">>" + username + " joined the chat! <<";
    send_message(connected);
}

void Client::disconnect_client()
{
    Glib::ustring disconnected = ">>" + username + " exited the chat! <<";
    send_message(disconnected);
}

// Destroy Client
Client::~Client()
{
    delete socket;
}

void Client::run(Window* caller)
{
    char initialMessage[MAX_MESSAGE_SIZE];

    {
        Glib::Threads::Mutex::Lock lock(mutex);
        isRunning = true;
        this->message = "";
    }

    socket->connect();

    // lê a mensagem inicial do servidor
    read(socket->getFd(), initialMessage, sizeof(initialMessage));

    if (std::strcmp(initialMessage, "Connection succeed")) {
        isRunning = false;
        return;
    }

    connect_client();

    // loop principal de comunicação
    while (isRunning) {
        char message[MAX_MESSAGE_SIZE];
        Glib::Threads::Mutex::Lock lock(mutex);

        if (recv(socket->getFd(), message, MAX_MESSAGE_SIZE, 0) <= 0) {
            raise(SIGTERM);
            break;
        }

        this->message = std::string { message };

        lock.release();
        caller->notify();
    }

    isRunning = false;
}

void Client::send_message(Glib::ustring message) const
{
    message.resize(MAX_MESSAGE_SIZE);
    send(socket->getFd(), (const void*)message.c_str(), message.size(), 0);
}

void Client::get_message(Glib::ustring* message) const
{
    if (message)
        *message = this->message;
}

void Client::set_username(Glib::ustring user)
{
    username = user;
}

bool Client::has_stopped() const
{
    return !isRunning;
}
