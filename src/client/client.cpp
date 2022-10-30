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
    message = ">> " + username + " joined the chat! <<";
    send_message(message);
}

void Client::disconnect_client()
{
    message = ">> " + username + " exited the chat! <<";
    send_message(message);
}

// Destroy Client
Client::~Client()
{
    delete socket;
}

void Client::run(Window* caller)
{   

    if(socket->connect() == -1){
        caller->server_is_down();
        while(socket->connect() == -1){

        }
    }

    std::cout << socket->connect();
    char initialMessage[MAX_MESSAGE_SIZE];

    {
        Glib::Threads::Mutex::Lock lock(mutex);
        isRunning = true;
        this->message = "";
    }

    
    
    // lê a mensagem inicial do servidor
    read(socket->getFd(), initialMessage, sizeof(initialMessage));

    if (std::strcmp(initialMessage, "Connection succeed")) {
        isRunning = false;
        return;
    }

    connect_client();
    caller->notify();

    // loop principal de comunicação
    while (isRunning) {
        char message[MAX_MESSAGE_SIZE];
        Glib::Threads::Mutex::Lock lock(mutex);

        if (recv(socket->getFd(), message, MAX_MESSAGE_SIZE, 0) <= 0) {
            raise(SIGTERM);
            break;
        }

        this->message = Glib::ustring { message };

        lock.release();
        caller->notify();
    }

    isRunning = false;
}

void Client::send_message(Glib::ustring message) const
{
    message.resize(MAX_MESSAGE_SIZE);
    send(socket->getFd(), (const void*)message.c_str(), message.size(), 0);
    message.empty();
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

Glib::ustring Client::get_username() const
{
    return username;
}

bool Client::has_stopped() const
{
    return !isRunning;
}
